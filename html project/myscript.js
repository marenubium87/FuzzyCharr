//constructor for phrase object

class Statement {
    //constructor for statement object
    constructor(isClue, isActive, isSolved, clueText, answerText) {
        this.isClue = isClue;
        this.isActive = isActive;
        this.isSolved = isSolved;
        this.clueText = clueText;
        this.answerText = answerText;
    }

    //picks the correct phrase in a statement, whether it be the clue or the answer
    pickPhrase() {
        var target;
        var arr = [];
        //debugger;
        //has this portion been solved?
        if (this.isSolved) {
            target = this.answerText;
        } 
        else {
            //debugger;
            target = this.clueText;
            if(this.isClue) {
                arr += '[ ';
            }
        }
        
        for (let i = 0; i < target.length; i++) {
            //debugger;
            if (typeof target[i] === "string") {
                arr += target[i];
            }
            else {
                arr += target[i].pickPhrase();
            }
        }

        //if unsolved clue, append trailing bracket
        if (!this.isSolved && this.isClue) {
        arr += ' ]';
        }
        return arr;
    }
}

var text5 = new Statement(true, true, false, ["the opposite of out"], "in");
var text4 = new Statement(true, true, false, ["plump like an overfed kitty"], "round");
var text2 = new Statement(true, true, false, ["the number one of something"], "best");
var text3 = new Statement(true, false, false, [text4, ", and not flat, thing that we live ", text5], "world");


var gameObject = {};
gameObject['baseStatement'] = new Statement(false, false, false, ["Cats are the ", text2, " creatures in the ", 
    text3, "."], "");
gameObject['cluesArr'] = [text2, text3, text4, text5];
gameObject['answersArr'] = [];
gameObject['isSolved'] = false;

//finds the answers to every clue in the puzzle and places into array
gameObject['populateAnswerList'] = function() {
    for (let i = 0; i < this.cluesArr.length; i++) {
        if (this.cluesArr[i].isClue) {
            this.answersArr.push(this.cluesArr[i].answerText);
        }
    }
}

gameObject['processGuess'] = function(guess) {
    
    var i = this.answersArr.indexOf(guess);
    document.getElementById("testOutput").textContent = i;

    if (i > -1) {

        if (this.cluesArr[i].isActive) {
            //debugger;
            
            this.cluesArr[i].isActive = false;
            this.cluesArr[i].isSolved = true;
            document.getElementById("testOutput").textContent = i;
            
            //now we need to figure out who is still active
            for (let j = 0; j < this.cluesArr.length; j++) {

                //active clues are ones who are not solved
                //but whose children are all solved
                if (!this.cluesArr[j].isSolved) {

                    //document.getElementById("testOutput").textContent = j;
                    var allChildrenSolved = true;

                    for(let k = 0; k < this.cluesArr[j].clueText.length; k++) {
                        //debugger;
                        if (this.cluesArr[j] instanceof Statement &&
                            this.cluesArr[j].clueText[k].isSolved === false) {
                                //debugger;
                            allChildrenSolved = false;
                            break;
                        }
                        
                    }

                    if (allChildrenSolved) {
                        this.cluesArr[j].isActive = true;
                    }
                }
            }
        }
    }
}

//window.onload is a *property* and not a function, so do not do window.onload() with the parens
window.onload = function() {
    //first display the raw unsolved phrase onto the webpage
    document.getElementById("puzzleStr").textContent=gameObject.baseStatement.pickPhrase();

    //populate the answers array in gameObject
    gameObject.populateAnswerList();

    const userGuess = document.getElementById("userGuess");
    
    userGuess.addEventListener('keydown', function(e) {
        if (e.key === 'Enter') {
            processGuess(userGuess.value);
            userGuess.value = "";
        }
    });
};

//adds event listener so that user can trigger guess by the Enter key after each guess

function processGuess(guess) {
    gameObject.processGuess(guess);
    document.getElementById("puzzleStr").textContent=gameObject.baseStatement.pickPhrase();
}