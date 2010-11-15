import Qt 4.7

SmallText {
  property Item item
  onItemChanged: if(item) text = item.name;
  width: parent.width / 2;
}
