import Qt 4.7

Image {
  id: battleEnemy;
  property Item character;
  source: {
    if(character && character.portrait)
      character.portrait;
    else
      '';
  }

  Component.onCompleted: {
    console.log("created battle enemy: " + parent.foo );
  }
}
