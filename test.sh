#./polygonization -i ../images/euro-night-0010000.instance -o output.txt -algorithm incremental -edge_selection 3 -initialization 1a
./polygonization -i ../images/euro-night-0000100.instance -o output.txt -algorithm incremental -edge_selection 2 -initialization 2a
#valgrind --leak-check=full ./polygonization -i ../images/euro-night-0001000.instance -o output.txt -algorithm incremental -edge_selection 3 -initialization 1a
#./polygonization -i ../images/euro-night-0000200.instance -o output.txt -algorithm convex_hull -edge_selection 1
#./polygonization -i ../images/uniform0000050-1.instance -o output.txt -algorithm convex_hull -edge_selection 1
#./polygonization -i ../images/uniform0000050-1.instance -o output.txt -algorithm convex_hull -edge_selection 1
