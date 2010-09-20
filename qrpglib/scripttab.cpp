#include "scripttab.h"
#include "globals.h"
#include "jshighlighter.h"

ScriptTab::ScriptTab(int condition, QString script) : QFrame(0) {
  layout = new QVBoxLayout;
  setLayout(layout);

  formLayout = new QFormLayout;
  layout->addLayout(formLayout);

  conditionSelect = new QComboBox;
  conditionSelect->addItems(ScriptCondition::conditions());
  conditionSelect->setCurrentIndex(condition);
  formLayout->addRow("Condition", conditionSelect);

  QFont font;
  font.setFamily("Monospace");
  font.setFixedPitch(true);
  font.setPointSize(10);

  scriptText = new QTextEdit;
  scriptText->setFont(font);
  highlighter = new JsHighlighter(scriptText->document());
  scriptText->setPlainText(script);
  layout->addWidget(scriptText);
}

