#./polygonization -i ../images/euro-night-0010000.instance -o output.txt -algorithm incremental -edge_selection 3 -initialization 1a
#./polygonization -i ../images/euro-night-0000100.instance -o output.txt -algorithm incremental -edge_selection 2 -initialization 2a
#valgrind --leak-check=full ./polygonization -i ../images/euro-night-0001000.instance -o output.txt -algorithm incremental -edge_selection 3 -initialization 1a
#./polygonization -i ../images/euro-night-0000200.instance -o output.txt -algorithm convex_hull -edge_selection 1
#./optimal_polygon -i ../images/euro-night-0000100.instance -o output.txt -algorithm simulated_annealing -edge_selection 2 -initialization 2a
#./optimal_polygon -i ../images/euro-night-0000100.instance -o output.txt -algorithm simulated_annealing -max -annealing local -L 10
./optimal_polygon -i uniform-0000050-1.instance -o output.txt -algorithm local_search -L 10 -max -threshold 50.0
#./optimal_polygon -i ../images/euro-night-0000100.instance -o output.txt -algorithm simulated_annealing -L 10  -annealing local -max