import Qt 4.7

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

  function activate(user, targets) {
    // override on a per-ability basis
  }
}
