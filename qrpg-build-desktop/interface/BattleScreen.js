var characterBoxes;
var characterBoxComponent;
var battleEnemyComponent
var enemyParty;

function startUp() {
  characterBoxes = new Array();
  enemyParty = new Array();
  characterBoxComponent = Qt.createComponent("CharacterBox.qml");
  battleEnemyComponent = Qt.createComponent("BattleEnemy.qml");
}

function newBattleEnemy(p, enemy) {
  console.log("about to create enemy: " + p.foo);
  var b = battleEnemyComponent.createObject(p);
  b.character = enemies[enemy].copy();
  console.log("enemy portait: " + b.source);
  return b;
}
