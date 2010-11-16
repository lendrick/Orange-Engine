import Qt 4.7
import "Ability.js" as AbilityScript

Item {
  visible: false
  id: ability

  property string name

  property bool targetSelf
  property bool targetFriends
  property bool targetEnemies
  property bool targetMultiple

  property bool useableInBattle
  property bool useableOutsideBattle

  property int mpCost

  //Component.onCompleted: AbilityScript.startUp();

  /*
  function abilityScript() {
    console.log(name + " abilityScript()");
    return AbilityScript.abilityScript;
  }
  */

  function setActivateFunction(a) {
    /*
    rpgx.dumpScriptObject(a);
    rpgx.dumpScriptObject(a.arguments);
    rpgx.dumpScriptObject(a.callee);
    rpgx.dumpScriptObject(a.caller);
    rpgx.dumpScriptObject(a.length);
    rpgx.dumpScriptObject(a.name);
    */
    console.log("Setting activateFunction for " + name + " " + a);
    AbilityScript.abilityScript = a;
    //a.activate(null, null);
  }

  function activate(user, targets) {
    //rpgx.dumpScriptObject(AbilityScript.abilityScript);
    AbilityScript.activate(user, targets);
    //abilityScript.call(this, user, targets);
    //AbilityScript.abilityScript(user, targets);
  }
}
