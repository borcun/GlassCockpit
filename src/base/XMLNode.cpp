#include <cstdlib>
#include <cstring>
#include "XMLNode.h"
#include "Debug.h"

XMLNode::XMLNode(void) {

}

XMLNode::XMLNode(xmlNode *node) : m_node(node) {

}

XMLNode::~XMLNode() {

}

bool XMLNode::HasChild(const std::string &name) {
  return GetChild(name).IsValid();
}

std::string XMLNode::GetText() {
  // Little dance to avoid memory leak...
  const char *tmp = (const char *) xmlNodeGetContent(m_node->children);
  std::string ret(tmp);
  
  xmlFree((void *) tmp);

  return ret;
}

bool XMLNode::IsValid() {
  return m_node != NULL;
}

std::string XMLNode::GetName() {
  return std::string((const char *) m_node->name);
}

double XMLNode::GetTextAsDouble() {
  return strtod(GetText().c_str(), NULL);
}

int XMLNode::GetTextAsInt() {
  return strtol(GetText().c_str(), NULL, 0);
}
		
bool XMLNode::GetTextAsBool() {
  std::string text = GetText();  
  return text == "1" || text == "true" ||text == "TRUE" || text == "True";
}

void XMLNode::GetTextAsCoord(double &x, double &y) {
  std::string text = GetText();
  
  Assert(text.find(',',0) != std::string::npos, "coordinates must contain a comma");
  /// @todo remove sscanf
  sscanf(text.c_str(), "%lf,%lf", &x, &y);

  return;
}

XMLNode XMLNode::GetChild(const std::string &name) {
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      if (strcmp((const char *) curNode->name, name.c_str()) == 0) {
	return XMLNode(curNode);
      }
    }
  }

  return XMLNode();
}

bool XMLNode::HasProperty(const std::string &name) {
  return GetProperty(name) != "";
}

std::string XMLNode::GetProperty(const std::string &name) {
  std::string retval;
  
  for (xmlAttr *prop = m_node->properties; nullptr != prop; prop = prop->next) {
    if (strcmp((const char *) prop->name, name.c_str()) == 0) {
      const char *val = (const char *) xmlNodeGetContent(prop->children); 

      retval = val;
      xmlFree((void *) val);

      break;
    }
  }
	
  return retval;
}

std::list<XMLNode> XMLNode::GetChildList() {
  std::list<XMLNode> nodeList;
	
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      nodeList.push_back(XMLNode(curNode));
    }
  }

  return nodeList;
}

std::list<XMLNode> XMLNode::GetChildList(const std::string &name) {
  std::list<XMLNode> nodeList;
	
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      if (strcmp((const char*)curNode->name, name.c_str()) == 0) {
	nodeList.push_back(XMLNode(curNode));
      }
    }
  }

  return nodeList;
}
