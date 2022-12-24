include_directories(../headers)
add_library(utils utils.cpp)
add_library(incremental incremental.cpp)
add_library(convex_hull convex_hull.cpp)
<<<<<<< HEAD
add_library(local_search local_search.cpp incremental.cpp)
add_library(simulated_annealing simulated_annealing.cpp incremental.cpp)
=======
add_library(local_search local_search.cpp)
add_library(simulated_annealing simulated_annealing.cpp incremental.cpp)
add_library(subdivision_annealing subdivision_annealing.cpp incremental.cpp)
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
