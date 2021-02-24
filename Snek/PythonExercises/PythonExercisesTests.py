# Python exercises
# Taken from CptS 355, Spring 2020, Sakire Arslan-Ay

import unittest
from PythonExercises import *

class HW3SampleTests(unittest.TestCase):
    def setUp(self):
        pass

    def test_sumSales(self):
        salesLog= {'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200}, 'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}}
        summedLog = {'Fri': 30, 'Mon': 80, 'Sat': 220, 'Thu': 80, 'Tue': 180, 'Wed': 225}
        self.assertDictEqual(sumSales(salesLog),summedLog)

    def test_sumSalesN(self):
        salesLogN = [{'Barnes & Noble':{'Mon':30,'Wed':100,'Sat':200}, 'Etsy':{'Mon':50,'Tue':20,'Wed':25,'Fri':30}, 'Sur La Table':{'Tue':60,'Wed':100,'Thu':30}, 'Williams-Sonoma':{'Tue':100,'Thu':50,'Sat':20}}, {'Williams-Sonoma':{'Mon':25}, 'Etsy':{'Thu':40, 'Fri':50}, 'Sur La Table':{'Mon':100,'Sat':30}}, {'Barnes & Noble':{'Sun':88}, 'Etsy':{'Fri':55}, 'Sur La Table':{'Mon':40}, 'Williams-Sonoma':{'Sat':35}}]
        summedLogN = {'Fri': 135, 'Mon':245, 'Sat':285, 'Sun': 88, 'Thu': 120, 'Tue':180, 'Wed':225}

    def test_searchDicts(self):
        #searchDicts inputs
        dictList = [{"x": 1, "y": True, "z": "found"}, {"x": 2}, {"y": False}]
        self.assertEqual(searchDicts(dictList, "t"), None)

    def test_searchDicts2(self):
        dictList2 = [(0,{"x":0,"y":True,"z":"zero"}), (0,{"x":1}), (1,{"y":False}), (1,{"x":3, "z":"three"}), (2,{})]

    def test_busStops(self):
        routes = {
            "Lentil": ["Chinook", "Orchard", "Valley", "Emerald","Providence", "Stadium", "Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart", "Bishop", "Derby", "Dilke"],
            "Wheat": ["Chinook", "Orchard", "Valley", "Maple","Aspen", "TerreView", "Clay", "Dismores", "Martin", "Bishop", "Walmart", "PorchLight", "Campus"],
            "Silver": ["TransferStation", "PorchLight", "Stadium", "Bishop","Walmart", "Shopco", "RockeyWay"],
            "Blue": ["TransferStation", "State", "Larry", "TerreView","Grand", "TacoBell", "Chinook", "Library"],
            "Gray": ["TransferStation", "Wawawai", "Main", "Sunnyside","Crestview", "CityHall", "Stadium", "Colorado"]
        }
        self.assertEqual(busStops(routes,"Stadium"),['Lentil', 'Silver', 'Gray'])

    def test_palindromes(self):
        print("Test code goes here")


if __name__ == '__main__':
    unittest.main()
