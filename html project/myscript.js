//constructor for phrase object

class Phrase {
    //constructor for phrase object
    constructor(isClue, isActive, isSolved, phraseText, answerText) {
        this.isClue = isClue;
        this.isActive = isActive;
        this.isSolved = isSolved;
        this.phraseText = phraseText;
        this.answerText = answerText;
    }
      
    pickPhrase() {
        var target;
        var arr = [];
        if (this.isSolved) {
            target = this.answerText;
        } 
        else {
            target = this.phraseText;
            if(this.isClue) {
                arr += '['
            }
        }
        
        for (let i = 0; i < target.length; i++) {
        if (typeof target[i] === "string") {
            arr += target[i];
        }
        else {
            arr += target[i].pickPhrase();
        }
        }
        if (!this.isSolved && this.isClue) {
        arr += ']';
        }
        return arr;
    }
}

const text3 = new Phrase(true, true, false, ["can't fit a round peg into a square this"], "hole");
const text2 = new Phrase(true, false, false, ["like every w", text3, " number"], "even");
const text1 = new Phrase(false, false, false, [text2, " you can help stop forest fires!"]);

//window.onload is a *property* and not a function, so do not do window.onload() with the parens
window.onload = function() {
    document.getElementById("puzzleStr").textContent=text1.pickPhrase();
};

