# coding: utf-8
import re, random, time
from collections import defaultdict

from numpy import append

f = open('twl06.txt','r').read()
WORDS = [w for w in f.lower().splitlines() if len(w) == 5]
GUESSLIST = []

class Wordle:
	MATCH_CHAR = 				'm'
	CLOSE_MATCH_CHAR = 	'c'
	NO_MATCH_CHAR = 		'x'
	
	words = []
	bannedChars = set()
	
	secretWord = ''

	def __init__(self):
		self.words = WORDS[::]
		self.bannedChars = set()

	def matcher(self, guess, w2):
		letterCounts = defaultdict(int)
		for l in w2:
			letterCounts[l] += 1
			
		result = ''
		w2set = set(w2)
		for i, c in enumerate(guess):
			letterCounts[c] -= 1
			if c == w2[i]:
				result += self.MATCH_CHAR
			elif c in w2set and letterCounts[c] >= 0:
				result += self.CLOSE_MATCH_CHAR
			else:
				result += self.NO_MATCH_CHAR
		return result

	def reduceWords(self, guess, result):
		for i, c in enumerate(guess):
			if result[i] == self.NO_MATCH_CHAR:
				self.bannedChars.add(c)
			
		# cycle second time to cover cases where a letter is said not to be present but actually is a match in some cases	
		for i, c in enumerate(guess):
			if (result[i] == self.MATCH_CHAR or result[i] == self.CLOSE_MATCH_CHAR) and c in self.bannedChars:
					self.bannedChars.remove(c)
				
		self.words = [w for w in self.words if self.matcher(guess, w) == result and not self.hasBannedChars(w, self.bannedChars)]
	
	def hasBannedChars(self, word, bannedChars):
		for c in word:
			if c in bannedChars:
				return True
		return False
		
	def randomGuess(self):
		guess = random.choice(self.words)
		print(f'my guess: {guess}')
		
		matchString = input("how'd I do?\n")
		if matchString == 'mmmmm':
			self.__init__()
			print('Winner!')
			return
		elif matchString == 'q':
			print('Game quit')
			return
		
		self.reduceWords(guess, matchString)
		
		print(f'{len(self.words)} possible words remaining\n')
	
	def populateGuessList(self, g):
		g.append("cloud")
		g.append("empty")
		g.append("rains")

	def guessStrat(self, mainList, auxList):
		if len(mainList) > 0:
			x = mainList[0]
			mainList.pop(0)
			return x
		else:
			x = random.choice(auxList)
			return x



	def playGame(self):
		self.secretWord = random.choice(self.words)
		num_of_guesses = 0
		guesses = []
		while len(self.words) > 0:
			num_of_guesses += 1
			guess = self.guessStrat(GUESSLIST, self.words)
			#guess = random.choice(self.words)
			guesses.append(guess)
			
			if guess == self.secretWord:
				return Result(num_of_guesses, guesses, self.secretWord)
				
			result = self.matcher(guess, self.secretWord)
			self.reduceWords(guess, result)
			
		return -1

class Result:
	def __init__(self, score, guesses, answer):
		self.score = score
		self.guesses = guesses
		self.answer = answer
		
	def __str__(self):
		return str([str(self.score), str(self.guesses), str(self.answer)])
		
		
def montecarlo(num_of_plays):
	start_time = time.time()
	print(f'playing {num_of_plays} games')
	results = []
	scores = []
	for i in range(num_of_plays):
		game = Wordle()
		game.populateGuessList(GUESSLIST)
		result = game.playGame()
		results.append(result)
	results.sort(key = lambda result : result.score)
	
	scores = [r.score for r in results]
	runtime = time.time() - start_time
	
	print()
	print(f'runtime: {round(runtime,2)}s')
	print(f'avg of games = {sum(scores)/len(scores)}')
	print(f'25 percentile of games = {scores[len(scores)//4]}')
	print(f'median of games = {scores[len(scores)//2]}')
	print(f'75 percentile of games = {scores[len(scores)-(len(scores)//4)]}')
	print(f'max score = {max(scores)}')
	print(f'best score = {min(scores)}')
	
	worst_result = max(results, key = lambda r : r.score)
	print(f'worst game = {worst_result}')
	
	return scores
			

if __name__ == '__main__':
	scores = montecarlo(1500)
	game = Wordle()
	while True:
		game.randomGuess()
