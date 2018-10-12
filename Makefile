TESTS=base curry

%: test/%.cpp
	g++ -std=c++1z -Iinc -o $@ $<

test: $(TESTS)
	for i in $(TESTS); do ./$$i; done

clean:
	-rm $(TESTS)
