#include <cstdlib>
#include <cstring>
#include "xml_node.h"
#include "debug.h"

XMLNode::XMLNode(void) {

}

XMLNode::XMLNode(xmlNode *node) : m_node(node) {

}

XMLNode::~XMLNode() {

}

XMLNode XMLNode::getChild(const std::string &name) {
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      if (strcmp((char *) curNode->name, name.c_str()) == 0) {
	return XMLNode(curNode);
      }
    }
  }

  return XMLNode();
}

std::list<XMLNode> XMLNode::getChildList(void) {
  std::list<XMLNode> nodeList;
	
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      nodeList.push_back(XMLNode(curNode));
    }
  }

  return nodeList;
}

std::list<XMLNode> XMLNode::getChildList(const std::string &name) {
  std::list<XMLNode> nodeList;
	
  for (xmlNode *curNode = m_node->children; nullptr != curNode; curNode = curNode->next) {
    if (curNode->type == XML_ELEMENT_NODE) {
      if (strcmp((char *) curNode->name, name.c_str()) == 0) {
	nodeList.push_back(XMLNode(curNode));
      }
    }
  }

  return nodeList;
}

bool XMLNode::hasChild(const std::string &name) {
  return getChild(name).isValid();
}

std::string XMLNode::getText(void) {
  char *tmp = (char *) xmlNodeGetContent(m_node->children);
  std::string ret(tmp);
  
  xmlFree(tmp);

  return ret;
}

bool XMLNode::isValid(void) {
  return m_node != NULL;
}

std::string XMLNode::getName(void) {
  return std::string((char *) m_node->name);
}

double XMLNode::getTextAsDouble(void) {
  return strtod(getText().c_str(), NULL);
}

int XMLNode::getTextAsInt(void) {
  return strtol(getText().c_str(), NULL, 0);
}
		
bool XMLNode::getTextAsBool(void) {
  std::string text = getText();  
  return text == "1" || text == "true" ||text == "TRUE" || text == "True";
}

void XMLNode::getTextAsCoord(double &x, double &y) {
  std::string text = getText();
  
  Assert(text.find(',',0) != std::string::npos, "coordinates must contain a comma");
  /// @todo remove sscanf
  sscanf(text.c_str(), "%lf,%lf", &x, &y);

  return;
}

bool XMLNode::hasProperty(const std::string &name) {
  return !getProperty(name).empty();
}

std::string XMLNode::getProperty(const std::string &name) {
  std::string retval;
  
  for (xmlAttr *prop = m_node->properties; nullptr != prop; prop = prop->next) {
    if (strcmp((const char *) prop->name, name.c_str()) == 0) {
      char *val = (char *) xmlNodeGetContent(prop->children); 

      retval = val;
      xmlFree(val);

      break;
    }
  }
	
  return retval;
}
