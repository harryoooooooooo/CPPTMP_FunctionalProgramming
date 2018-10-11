%: test/%.cpp
	g++ -std=c++1z -Iinc -o $@ $<
