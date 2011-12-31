var characterBoxes;
var characterBoxComponent;
var battleEnemyComponent
var enemyParty;
var currentTurn;
var currentIndex;
var inBattle;

function startUp() {
  characterBoxes = new Array();
  enemyParty = new Array();
  characterBoxComponent = Qt.createComponent("CharacterBox.qml");
  battleEnemyComponent = Qt.createComponent("BattleEnemy.qml");
  currentTurn = "Characters";
  currentIndex = 0;
  inBattle = true;
}

function newBattleEnemy(p, enemy) {
  console.log("about to create enemy: " + p.foo);
  var b = battleEnemyComponent.createObject(p);
  b.character = enemies[enemy].copy();
  console.log("enemy portait: " + b.source);
  enemyParty.push(b);
  return b;
}

function nextCombatant() {
  console.log("party index: " + currentIndex);
  currentIndex++;
  if(currentTurn == "Characters" && currentIndex >= party.length) {
    //currentTurn = "Enemies";
    currentIndex = 0;
  } else if(currentTurn == "Enemies" && currentIndex >= enemyParty.length) {
    currentTurn = "Characters";
    currentIndex = 0;
  }

  if(currentTurn == "Characters") {
    console.log("Next party combatant: " + party[currentIndex].name);
  } else {
    console.log("Next enemy combatant: " + enemyParty[currentIndex].name);
  }
}
