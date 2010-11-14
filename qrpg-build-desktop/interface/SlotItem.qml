import Qt 4.7

StatItem {
  statValueItem.x: 0
  statValueItem.y: statTitleItem.height
  statTitleItem.font.bold: true
  statValueItem.color: if(value == 'none') '#999'; else '#fff'
}
