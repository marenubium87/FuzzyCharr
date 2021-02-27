# Python exercises
# Taken from CptS 355, Spring 2020, Sakire Arslan-Ay

import unittest
from PythonExercises import *

class HW3SampleTests(unittest.TestCase):
    def setUp(self):
        pass

    def test_sumSales(self):
        salesLog= {'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200}, 
                   'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 
                   'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 
                   'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}}
        summedLog = {'Fri': 30, 'Mon': 80, 'Sat': 220, 
                     'Thu': 80, 'Tue': 180, 'Wed': 225}
        self.assertDictEqual(sumSales(salesLog),summedLog)
        
        salesLog2 = {'Kitty\'s Catnip Emporium': {'Mon':120, 'Tue':120, 'Sat':300},
                     'Moocow Ltd.': {'Tue': 300, 'Wed':80, 'Fri':100},
                     'Very Sad Store':{},
                     'Only Open Thursdays':{'Thu':600}
                     }
        summedLog2 = {'Mon':120, 'Tue':420, 'Wed':80, 'Thu':600,
                      'Fri':100, 'Sat':300}
        self.assertDictEqual(sumSales(salesLog2), summedLog2)

        salesLog3 = {'Sixty Nine R Us': {'Mon':69, 'Thu':60, 'Fri':40,
                                         'Sat':33, 'Sun':60},
                     'Also Sixty Nine': {'Tue':40, 'Thu':9, 'Sat':33, 'Sun':5},
                     'Fifty + Nineteen': {'Tue':29, 'Wed':62, 'Fri':24, 'Sat':3},
                     'Twenty Three Times Three': {'Wed':7, 'Fri':5, 'Sun':4}
                     }
        summedLog3 = {'Mon':69, 'Tue':69, 'Wed':69, 'Thu':69,
                      'Fri':69, 'Sat':69, 'Sun':69}
        self.assertDictEqual(sumSales(salesLog3), summedLog3)
 
    def test_sumSalesN(self):
        salesLogN = [{'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200}, 
                      'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 
                      'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 
                      'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}}, 
                     
                     {'Williams-Sonoma':{'Mon':25}, 
                      'Etsy':{'Thu':40, 'Fri':50}, 
                      'Sur La Table':{'Mon':100,'Sat':30}}, 
                      
                     {'Barnes & Noble':{'Sun':88}, 
                      'Etsy':{'Fri':55}, 
                      'Sur La Table':{'Mon':40}, 
                      'Williams-Sonoma':{'Sat':35}}
                    ]
        summedLogN = {'Fri': 135, 'Mon':245, 'Sat':285, 'Sun': 88, 'Thu': 120, 'Tue':180, 'Wed':225}
        self.assertDictEqual(sumSalesN(salesLogN),summedLogN)

        salesLogN2 = [{'MooCow Emporium':{'Mon':190,'Wed':100,'Sat':200}, 
                      'Angry Kitty':{'Tue':20,'Wed':25,'Thu':50,'Fri':30}, 
                      'Surly Table':{'Tue':60,'Fri':100,'Sat':30}, 
                      'TastyBirb Inc.':{'Tue':100,'Thu':50,'Sat':20}}, 
                     
                     {'MooCow Emporium':{'Tue':25, 'Wed':75}, 
                      'Bob Dole Pineapples':{'Thu':40, 'Fri':50, 'Sun':100}, 
                      'Surly Table':{'Mon':100,'Fri':100, 'Sat':20}}, 
                      
                     {'Books or Something':{'Thu':50, 'Sun':90}, 
                      'Angry Kitty':{'Fri':25}}
                    ]
        summedLogN2 = {'Mon':290,'Tue':205,'Wed':200,'Thu':190,'Fri':305,'Sat':270, 'Sun':190}
        self.assertDictEqual(sumSalesN(salesLogN2),summedLogN2)

        salesLogN3 = [{'Mississippi':{'Mon':120,'Wed':100,'Sat':110}, 
                      'Rhine':{'Tue':20,'Wed':25,'Thu':50,'Fri':45}, 
                      'Volga':{'Tue':25,'Fri':55,'Sat':30}, 
                      'Nile':{'Tue':45,'Thu':50,'Sat':20}}, 
                     
                     {'Nile':{'Tue':25, 'Wed':75}, 
                      'Rhine':{'Thu':40, 'Fri':50, 'Sun':40}, 
                      'Volga':{'Mon':80,'Fri':50, 'Sat':20}}, 
                      
                     {'Volga':{'Thu':50, 'Sun':90}, 
                      'Mississippi':{'Fri':25}},

                     {'Mississippi':{'Mon':25, 'Thu':40},
                      'Yangtze':{'Wed':120, 'Fri':80, 'Sat':30}},

                     {'Volga':{'Tue':100, 'Wed':50, 'Thu':25},
                      'Dneiper':{'Thu':245, 'Fri':100, 'Sat':50}}
                    ]
        summedLogN3 = {'Mon':225,'Tue':215,'Wed':370,'Thu':500,'Fri':405,'Sat':260, 'Sun':130}
        self.assertDictEqual(sumSalesN(salesLogN3),summedLogN3)

    def test_searchDicts(self):
        #searchDicts inputs
        dictList = [{"x": 1, "y": True, "z": "found"}, {"x": 2}, {"y": False}]
        self.assertEqual(searchDicts(dictList, "t"), None)
        self.assertEqual(searchDicts(dictList, "x"), 2)
        self.assertEqual(searchDicts(dictList, "z"), "found")
        self.assertEqual(searchDicts(dictList, "y"), False)

        dictList2 = [{"cat":20, "moo":"cow", "birb":"meat"},
                    {"cat":"evil", "birb":"toy", "pi":3.14},
                    {"cat":"sorcerer"}]
        self.assertEqual(searchDicts(dictList2, "cat"), "sorcerer")
        self.assertEqual(searchDicts(dictList2, "birb"), "toy")
        self.assertEqual(searchDicts(dictList2, "mrow"), None)
        self.assertEqual(searchDicts(dictList2, "pi"), 3.14)
        self.assertEqual(searchDicts(dictList2, "moo"), "cow")

        dictList3 = [{69:25, 70:21, 42:420, 43:1},
                    {69:7, 1:5, 32:80, 68:45},
                    {1:7, 26:78, 420:42, 6969:69},
                    {5:5, 7:7, 9:9, 11:11}]
        self.assertEqual(searchDicts(dictList3, 1), 7)
        self.assertEqual(searchDicts(dictList3, 4201), None)
        self.assertEqual(searchDicts(dictList3, 420), 42)
        self.assertEqual(searchDicts(dictList3, 9), 9)
        self.assertEqual(searchDicts(dictList3, 68), 45)
        self.assertEqual(searchDicts(dictList3, 43), 1)
        self.assertEqual(searchDicts(dictList3, 696969), None)

    def test_searchDicts2(self):

        dictListA = [(0,{"x":0,"y":True,"z":"zero"}), (0,{"x":1}), (1,{"y":False}), (1,{"x":3, "z":"three", "t":5}), (2,{})]
        self.assertEqual(searchDicts2(dictListA, "z"), "zero")
        self.assertEqual(searchDicts2(dictListA, "x"), 1)
        self.assertEqual(searchDicts2(dictListA, "t"), None)
        self.assertEqual(searchDicts2(dictListA, "y"), False)

        dictListB = [
            (0, {"x":0,"y":True}), 
            (0, {"x":1}), 
            (1, {"y":False}), 
            (2, {"x":3, "z":"three", "t":5}), 
            (0, {"a":5, "x":7, "k":5}),
            (4, {"a":6, "b":4})]
        self.assertEqual(searchDicts2(dictListB, "a"), 6)
        self.assertEqual(searchDicts2(dictListB, "x"), 7)
        self.assertEqual(searchDicts2(dictListB, "y"), True)
        self.assertEqual(searchDicts2(dictListB, "z"), None)
        self.assertEqual(searchDicts2(dictListB, "t"), None)

        dictListC = [
            (0, {1:73, 2:5, 6:9, 12:8}), 
            (0, {12:9}), 
            (1, {7:12, 24:7, 2:10}), 
            (2, {7:11}), 
            (2, {3:4, 4:5, 6:8}),
            (3, {5:5})]
        self.assertEqual(searchDicts2(dictListC, 1), 73)
        self.assertEqual(searchDicts2(dictListC, 3), None)
        self.assertEqual(searchDicts2(dictListC, 6), 9)
        self.assertEqual(searchDicts2(dictListC, 7), 11)
        self.assertEqual(searchDicts2(dictListC, 24), 7)
        self.assertEqual(searchDicts2(dictListC, 12), 9)
        self.assertEqual(searchDicts2(dictListC, 2), 10)

    def test_busStops(self):
        routes = {
            "Lentil": ["Chinook", "Orchard", "Valley", "Emerald","Providence", "Stadium", "Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart", "Bishop", "Derby", "Dilke"],
            "Wheat": ["Chinook", "Orchard", "Valley", "Maple","Aspen", "TerreView", "Clay", "Dismores", "Martin", "Bishop", "Walmart", "PorchLight", "Campus"],
            "Silver": ["TransferStation", "PorchLight", "Stadium", "Bishop","Walmart", "Shopco", "RockeyWay"],
            "Blue": ["TransferStation", "State", "Larry", "TerreView","Grand", "TacoBell", "Chinook", "Library"],
            "Gray": ["TransferStation", "Wawawai", "Main", "Sunnyside","Crestview", "CityHall", "Stadium", "Colorado"]
        }
        self.assertEqual(busStops(routes,"Stadium"),['Lentil', 'Silver', 'Gray'])
        self.assertEqual(busStops(routes,"Orchard"),['Lentil', 'Wheat'])
        self.assertEqual(busStops(routes,"Colorado"),['Gray'])
        self.assertEqual(busStops(routes,"Hell"),[])

        routes2 = {
            "Aquila": [1, 2, 3, 6, 9, 13, 15, 19],
            "Lyra":  [1, 3, 6, 8, 9, 10, 12, 14, 15],
            "Cygnus":  [2, 3, 4, 5, 8, 9, 10, 12, 16],
            "Pegasus": [3, 5, 7, 8, 11, 12, 13, 14, 15]
        }
        self.assertEqual(busStops(routes2, 1),["Aquila", "Lyra"])
        self.assertEqual(busStops(routes2, 3),["Aquila", "Lyra", "Cygnus", "Pegasus"])
        self.assertEqual(busStops(routes2, 8),["Lyra", "Cygnus", "Pegasus"])
        self.assertEqual(busStops(routes2, 18),[])
        self.assertEqual(busStops(routes2, 14),["Lyra", "Pegasus"])
        self.assertEqual(busStops(routes2, 16),["Cygnus"])

        routes3 = {
            "Counting": [1, 2, 3, 4, 5, 6, 7, 8, 9],
            "Integer": [1, -1, 2, -2, 3, -3, 4, -4],
            "Prime":  [2, 3, 5, 7, 11, 13],
            "Even": [2, 4, 6, 8, 10, 12]
        }
        self.assertEqual(busStops(routes3, 2),["Counting", "Integer", "Prime", "Even"])
        self.assertEqual(busStops(routes3, 4),["Counting", "Integer", "Even"])
        self.assertEqual(busStops(routes3, 7),["Counting", "Prime"])
        self.assertEqual(busStops(routes3, -1),["Integer"])
        self.assertEqual(busStops(routes3, 14),[])

    def test_palindromes(self):
        self.assertEqual(palindromes("abba"), ["abba", "bb"])
        self.assertEqual(palindromes("python"), [])
        self.assertEqual(palindromes("racecarvroom"), ["aceca", "cec", "oo", "racecar", "rvr"])
        self.assertEqual(palindromes("bookkeeper"), ["ee", "epe", "kk", "oo"])
        self.assertEqual(palindromes("boobieslulz"), ["boob", "lul", "oo"])

if __name__ == '__main__':
    unittest.main()
