#include "board.h"
#include <string>
#include "block.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {
        Board b;
        b.init(18, 11);
	auto bl = make_unique<Block>('J', 1);
	auto b2 = make_unique<Block>('Z', 1);
	b.setCurBlock(bl);
	b.setNextBlock(b2);
	cout << b.getNextBlock();
	cout << "SIZE : " << b.getCurBlock()->getCoOrd().size() << endl;
	b.drop();
	auto b3 = make_unique<Block>('I', 1);
	b.setNextBlock(b3);
	b.notifyObservers();
	cout << b;
	b.drop();
	auto b4 = make_unique<Block>('T', 1);
	b.setNextBlock(b4);
	b.right();
	b.right();
	b.right();
	b.drop();
	auto b5 = make_unique<Block>('L', 1);
	b.setNextBlock(b5);
	b.right();
	b.right();
	b.right();
	b.right();
	b.right();
	b.right();
	b.right();
	b.drop();
	auto b6 = make_unique<Block>('S',1);
	b.setNextBlock(b6);
        b.notifyObservers();
        cout << b;	
} 

