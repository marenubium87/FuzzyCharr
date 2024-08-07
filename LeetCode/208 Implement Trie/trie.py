class Trie:

    class TrieNode:
        
        def __init__(self):
            self.suffixes: dict = {}            
            self.is_terminal: bool = False

    def __init__(self):
        self.root = self.TrieNode()

    #inserts the string {word} into the trie
    def insert(self, word: str) -> None:
        # for each character, if it isn't found in the current layer's dict, 
        # make an entry and initialize the value to another TrieNode
        curr = self.root
        for c in word:
            if c in curr.suffixes.keys():
                curr = curr.suffixes[c]
            else:
                curr.suffixes[c] = self.TrieNode()
                curr = curr.suffixes[c]
        curr.is_terminal = True

    #returns true if string {word} is in trie, and false otherwise
    def search(self, word:str) -> bool:
        #basically the same as startswith, but with an extra check that there is a
        #terminate flag at the end of the search entry
        curr = self.root
        for c in word:
            if c in curr.suffixes:
                curr = curr.suffixes[c]
            else:
                return False
        return curr.is_terminal

    #returns true if previously inserted string {word} has the prefix {prefix}
    #and false otherwise
    def startsWith(self, prefix: str) -> bool:
        #we need all of the letters of prefix to exist in the trie
        curr = self.root
        for c in prefix:
            if c in curr.suffixes:
                curr = curr.suffixes[c]
            else:
                return False
        return True

my_trie = Trie()
my_trie.insert('cat')
my_trie.insert('catapult')
print(my_trie.startsWith('cabbage'))
print(my_trie.startsWith('c'))
print(my_trie.startsWith('catap'))
print(my_trie.startsWith('cat'))
print(my_trie.startsWith('dog'))
print(my_trie.search('cat'))
print(my_trie.search('catappult'))
print(my_trie.search('catapult'))
print(5)
