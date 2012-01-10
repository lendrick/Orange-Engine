/* 
 * The functions in this file are meant to be called by enemy objects
 * on that enemy's turn.
 * 
 * For instance:
 * enemy.turn = ai.random;
 */

var ai = new Object;

/*
 * This function chooses an enemy ability at random and uses it.
 */
ai.random = function(enemy, targets) {
    console.log("enemy: " + enemy.name);
    
    var abilities = enemy.getAbilityNames();
    serialize(abilities);
    var usable = new Array();
    for(var i in abilities) {
        if(abilities[i].useInBattle && abilities[i].mpCost <= enemy.mp) {
            usable.push(abilities[i]);
        }
    }
    var index = Math.floor(Math.random()*usable.length);
    var result = new Object();
    result.ability = usable[index];
    result.target = targets[Math.floor(Math.random() * targets.length)];
    console.log('random: ' + result.ability);
    return result;
}