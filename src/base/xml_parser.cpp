#include <iostream>
#include <cstring>
#include "xml_parser.h"
#include "Debug.h"

XMLParser::XMLParser() {
  // This initializes the library and checks that the ABI version matches the API version etc.
  LIBXML_TEST_VERSION

  xmlInitParser();
}

XMLParser::~XMLParser() {
  if (m_xml_doc != NULL) {
    xmlFreeDoc(m_xml_doc); // note this recursively free's all the nodes too
    m_xml_doc = NULL;
    m_xml_root_node = NULL;
  }

  xmlCleanupParser();
}

bool XMLParser::read(const char *filename) {
  if (nullptr == filename) {
    std::cerr << "invalid file name" << std::endl;
    return false;
  }
  
  // Parse the file and get the DOM
  m_xml_doc = xmlReadFile(filename, NULL, 0);

  if (m_xml_doc == NULL) {
    std::cerr << "Error: could not parse XML file \"" << filename << "\".\n";
    return false;
  }

  // Get the root element node
  m_xml_root_node = xmlDocGetRootElement(m_xml_doc);

  if (m_xml_root_node == NULL) {
    std::cerr << "Error: empty XML file \"" << filename << "\".\n";
    return false;
  }

  return true;
}

XMLNode XMLParser::getNode(const std::string &path) {
  XMLNode node = XMLNode(m_xml_root_node);
  unsigned long start_offset = 1, end_offset = 1;

  // First, check the path starts with "/"
  // (We don't handle relative paths here)
  Assert(path[0] == '/', "XMLNode path must start with '/'");
  
  if (path == "/") {
    return node; // At this point, node is m_xml_root_node
  }
  
  // Now iterate over each token in the path and get its node
  while (start_offset < path.size()) {
    // Find next "/" if there is one, otherwise the end of the string
    end_offset = path.find('/', start_offset);
    end_offset = (end_offset == std::string::npos) ? path.size() : end_offset;
	
    // Extract the "token" between the two slashes
    std::string tok = path.substr(start_offset, end_offset - start_offset);

    // Get the corresponding node
    node = node.getChild(tok);
    
    if (!node.isValid()) {
      break; // In this case, the invalid node is returned
    }
		
    start_offset = end_offset + 1;
  }

  return node;
}

bool XMLParser::hasNode(const std::string &path) {
  return getNode(path).isValid();
}

void XMLParser::print(xmlNode *aNode, const std::string &indentation) {
  // FIXME maybe use the XMLNode API instead of direct xmlNode manipulation
  // Deal with entry into the top of the recursion
  xmlNode *curNode = nullptr == aNode ? m_xml_root_node : aNode;

  // Now iterate and recurse
  while (nullptr != curNode) {
    if (curNode->type == XML_ELEMENT_NODE) {
      // Get the node name
      std::cout << indentation << curNode->name;

      // Get the properties/attributes
      for (xmlAttr *prop = curNode->properties; prop; prop = prop->next) {
	const xmlChar *val = xmlNodeGetContent(prop->children); 

	std::cout << " (" << prop->name << "=\"" << val << "\")";
	xmlFree((void *) val);
      }

      // Get the data/content
      const xmlChar *content = xmlNodeGetContent(curNode->children);

      // check presence of whitespace character into content
      if (content != NULL && nullptr == strchr((char *) content, ' ')) {
	std::cout << " = \"" << content << "\"\n";
      }
      else {
	std::cout << "\n";
      }
      
      xmlFree((void *) content);
			
      if (curNode->children != NULL) {
	print(curNode->children, indentation + "    ");
      }
    }

    curNode = curNode->next;
  }

  return;
}
