#include "JModal.h"
#include "JCanvas.h"
#include "JButton.h"
#include "JSeparator.h"
#include "JBorderLayout.h"
#include "JFlowLayout.h"

char* theJModal = JModal().Register();
int JModal::create() { 
  JModal *mb = (JModal*)createJModal(
    theJModal, theMainWindow);
  return (mb) ? mb->runModal() : CANCEL;
}

const char* JModal::className() const { return "JModal";}
JObject* JModal::clone() const { return new JModal(*this);}

int JModal::runModal() {
  show();
  return JComponent::runModal(handle);
}

void JModal::endModal(int _result) {
  result = _result;
  if (!transferArguments()) return;
  dispose();
}

boolean JModal::transferArguments() 
{ return true;}

boolean JModal::lostFocus(JEvent& e, JObject* arg) {
  if (!arg || (arg != this) &&
    !((JComponent*)arg)->isAncestor(*this)) {
    dispose();
  }
  return true;
}

