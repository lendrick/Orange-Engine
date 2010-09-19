#include "scripttab.h"
#include "globals.h"
#include "jshighlighter.h"

ScriptTab::ScriptTab(int condition, QString script, bool defBounds, int x1, int y1, int x2, int y2) : QFrame(0) {
  QVBoxLayout * layout = new QVBoxLayout;
  setLayout(layout);

  QFormLayout * formLayout = new QFormLayout;
  layout->addLayout(formLayout);

  conditionSelect = new QComboBox;
  conditionSelect->addItems(ScriptCondition::conditions());
  conditionSelect->setCurrentIndex(condition);
  formLayout->addRow("Condition", conditionSelect);

  useDefaultBoundingBox = new QCheckBox;
  useDefaultBoundingBox->setCheckState(Qt::Checked);
  formLayout->addRow("Use default bounds", useDefaultBoundingBox);

  c1 = new CoordinateWidget(0, x1, y1);
  formLayout->addRow("Upper left bound", c1);

  c2 = new CoordinateWidget(0, x2, y2);
  formLayout->addRow("Lower right bound", c2);

  QFont font;
  font.setFamily("Monospace");
  font.setFixedPitch(true);
  font.setPointSize(10);

  scriptText = new QTextEdit;
  scriptText->setFont(font);
  highlighter = new JsHighlighter(scriptText->document());
  scriptText->setPlainText(script);
  layout->addWidget(scriptText);

  connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c1, SLOT(setDisabled(bool)));
  connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c2, SLOT(setDisabled(bool)));

  if(defBounds) {
    useDefaultBoundingBox->setCheckState(Qt::Checked);
    c1->setDisabled(true);
    c2->setDisabled(true);
  } else {
    useDefaultBoundingBox->setCheckState(Qt::Unchecked);
    c1->setDisabled(false);
    c2->setDisabled(false);
  }

}

