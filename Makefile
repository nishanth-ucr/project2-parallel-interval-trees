ifdef CLANG
CC = clang++
else
CC = g++
endif

CPPFLAGS = -std=c++17 -Wall -Werror

ifdef CILKPLUS
CPPFLAGS += -DPARLAY_CILKPLUS -DCILK -fcilkplus
else ifdef SERIAL
CPPFLAGS += -DPARLAY_SEQUENTIAL
else
CPPFLAGS += -pthread
endif

ifdef DEBUG
CPPFLAGS += -Og -mcx16 -DDEBUG
else ifdef PERF
CPPFLAGS += -Og -mcx16 -march=native -g
else ifdef MEMCHECK
CPPFLAGS += -Og -mcx16 -DPARLAY_SEQUENTIAL
else ifdef MXMAC
CPPFLAGS += -O3 -mcpu=apple-m1
else
CPPFLAGS += -O3 -mcx16 -march=native
endif

HEADERFILES = interval_tree.h interval_trees_par.h interval_trees_seq.h interval_tree_utils.h

all: test_join1 test_join_2 test_insert1 test_build1 test_build2 test_split1 test_split_last1 test_union1 test_union2 test_intersection1 test_intersection2 test_difference1 test_difference2 test_delete1 test_query1

test_join1: test_join1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_join1.cpp -o test_join1

test_join_2: test_join_2.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_join_2.cpp -o test_join_2

test_insert1: test_insert1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_insert1.cpp -o test_insert1

test_build1: test_build1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_build1.cpp -o test_build1

test_build2: test_build2.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_build2.cpp -o test_build2

test_split1: test_split1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_split1.cpp -o test_split1

test_split_last1: test_split_last1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_split_last1.cpp -o test_split_last1

test_union1: test_union1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_union1.cpp -o test_union1

test_union2: test_union2.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_union2.cpp -o test_union2

test_intersection1: test_intersection1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_intersection1.cpp -o test_intersection1

test_intersection2: test_intersection2.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_intersection2.cpp -o test_intersection2

test_difference1: test_difference1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_difference1.cpp -o test_difference1

test_difference2: test_difference2.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_difference2.cpp -o test_difference2

test_delete1: test_delete1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_delete1.cpp -o test_delete1

test_query1: test_query1.cpp $(HEADERFILES)
	$(CC) $(CPPFLAGS) test_query1.cpp -o test_query1

clean:
	rm test_join1 test_join_2 test_insert1 test_build1 test_build2 test_split1 test_split_last1 test_union1 test_union2 test_intersection1 test_intersection2 test_difference1 test_difference2 test_delete1 test_query1
