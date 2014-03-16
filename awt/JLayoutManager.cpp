#include "JLayoutManager.h"
#include "JComponent.h"

char* theJLayoutManager = JLayoutManager().Register();
const char* JLayoutManager::className() const { return "JLayoutManager";}
JObject* JLayoutManager::clone() const { return new JLayoutManager(*this);}
void JLayoutManager::addLayoutComponent(int type, JComponent& comp) {}
void JLayoutManager::removeLayoutComponent(JComponent& comp) {}

JDimension JLayoutManager::preferredLayoutSize(JComponent& parent) 
{ return parent.size();}

JDimension JLayoutManager::minimumLayoutSize(JComponent& parent) 
{ return parent.size();}

void JLayoutManager::layout(JComponent& parent) {}
