//saving original statement while i play around with others

var text3 = new Statement(true, true, false, ["can't fit a round peg into a square ___"], "hole");
var text2 = new Statement(true, false, false, ["like every w", text3, " number multiplied by two"], "even");

var gameObject = {};
gameObject['baseStatement'] = new Statement(false, false, false, [text2, " you can learn to be a bobcat!"], "");
gameObject['cluesArr'] = [text2, text3];