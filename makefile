default: compile

compile: treap.cpp st.cpp rbt.cpp
	g++ treap.cpp -g -o treap
	g++ st.cpp -g -o st
	g++ rbt.cpp -g -o rbt