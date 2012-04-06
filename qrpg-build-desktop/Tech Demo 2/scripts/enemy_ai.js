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
ai.random = function(self, targets, friends) {
    console.log("enemy AI random: " + self.name);
    
    var abilities = self.getAbilityNames();
    var usable = new Array();
    for(var i in abilities) {
        console.log(abilities[i]);
        if(allAbilities[abilities[i]].useInBattle && allAbilities[abilities[i]].mpCost <= self.mp) {
            usable.push(abilities[i]);
            console.log("*usable");           
        }
    }
    var index = Math.floor(Math.random()*usable.length);
    var result = new Object();
    result.ability = usable[index];
    result.target = [targets[Math.floor(Math.random() * targets.length)]];
    console.log('random: ' + result.ability);
    return result;
}