var abilityScript;

function startUp() {
  console.log("init abilityscript");
}

function activate(user, targets) {
  console.log("Activating ability " + name);
  rpgx.dumpScriptObject(abilityScript);
  abilityScript(user, targets);
}
