#include <iostream>
#include <vector>
using namespace std;

enum class Category {
	Ack = 1,  //공격
	Def = 2,  //방어
	Hp = 3    //체력
};

class Item {
private:
	string itemName;
	int ack = 0;
	int def = 0;
	int hp = 0;
	int price = 0;
	string explanation;
	Category category;
public:
	Item(string itemName, int ack, int def, int hp, int price, string explanation, Category category) //constructor
		: itemName(itemName), ack(ack), def(def), hp(hp), price(price), explanation(explanation), category(category) {};
	string getItemName() { return itemName; }
	int getAck() { return ack; }
	int getDef() { return def; }
	int getHp() { return hp; }
	int getPrice() { return price; }
	string getExplanation() { return explanation; }
	Category getCategory() { return category; }
};

class Player {
private:
	int playerGold = 10000;
	int playerAck = 0;
	int playerDef = 0;
	int playerHp = 0;
	vector<Item> inventory;
public:
	//default constructor 
	int getGold()
	{
		return playerGold;
	}
	bool isInvenFull()
	{
		if (inventory.size() >= 6)
			return true;
		else
			return false;
	}
	bool isInvenEmpty()
	{
		if (inventory.size() == 0)
			return true;
		else
			return false;
	}
	//구매 실패하면 리턴값 -1
	bool buyItem(Item item) {
		// 골드가 충분한지 체크
		if (playerGold < item.getPrice()) {
			cout << "골드가 부족합니다!" << endl;
			return false;
		}

		// 인벤토리가 꽉 찼는지 체크
		if (isInvenFull()) {
			cout << "인벤토리가 가득 찼습니다!" << endl;
			return false;
		}

		// 구매 진행
		inventory.push_back(item);
		playerAck += item.getAck();
		playerDef += item.getDef();
		playerHp += item.getHp();
		playerGold -= item.getPrice();

		cout << item.getItemName() << "를 구매했습니다." << endl;

		switch (item.getCategory()) {
		case Category::Ack:
			cout << "플레이어의 공격력이 " << item.getAck() << " 상승하여 " << playerAck << "이 됩니다." << "\n";
			break;
		case Category::Def:
			cout << "플레이어의 방어력이 " << item.getDef() << " 상승하여 " << playerDef << "이 됩니다." << "\n";
			break;
		case Category::Hp:
			cout << "플레이어의 체력이 " << item.getHp() << " 상승하여 " << playerHp << "이 됩니다." << "\n";
			break;
		}
		cout << "보유한 골드가 " << item.getPrice() << "G 감소하여 " << playerGold << "G가 됩니다." << "\n";

		return true;
	}
	//판매 불가시 -1 리턴
	bool sellItem(int index) {
		// 인벤토리가 비었거나 잘못된 인덱스인 경우
		if (inventory.empty() || index < 0 || index >= inventory.size()) {
			cout << "유효하지 않은 아이템입니다." << endl;
			return false;
		}

		Item item = inventory[index];

		playerAck -= item.getAck();
		playerDef -= item.getDef();
		playerHp -= item.getHp();
		playerGold += item.getPrice();

		inventory.erase(inventory.begin() + index);
		cout << item.getItemName() << "를판매합니다" << "\n";

		switch (item.getCategory()) {
		case Category::Ack:
			cout << "플레이어의 공격력이 " << item.getAck() << " 하락하여 " << playerAck << "이 됩니다." << "\n";
			break;
		case Category::Def:
			cout << "플레이어의 방어력이 " << item.getDef() << " 하락하여 " << playerDef << "이 됩니다." << "\n";
			break;
		case Category::Hp:
			cout << "플레이어의 체력이 " << item.getHp() << " 하락하여 " << playerHp << "이 됩니다." << "\n";
			break;
		}
		cout << "보유한 골드가 " << item.getPrice() << "G 상승하여 " << playerGold << "G가 됩니다." << "\n";
		cout << endl;
		return true;
	}

	void displaystat()
	{
		cout << "\n";
		cout << "플레이어 골드 보유량 : " << playerGold << "G\n";
		cout << "플레이어 공격력 상승량 : " << playerAck << "\n";
		cout << "플레이어 방어력 상승량 : " << playerDef << "\n";
		cout << "플레이어 체력 상승량 : " << playerHp << "\n";
		cout << "\n";
	}

	void displayInventory()
	{
		if (inventory.empty()) {
			cout << "인벤토리가 비어있습니다." << endl;
			return;
		}

		for (int i = 0; i < inventory.size(); i++)
		{
			cout << i + 1 << ".  " << inventory[i].getItemName() << "\n";
			cout << "  가격 : " << inventory[i].getPrice() << "G" << "\n";
			cout << "  설명 : " << inventory[i].getExplanation() << "\n";
			switch (inventory[i].getCategory())
			{
			case Category::Ack:
				cout << "   공격력 상승 : " << inventory[i].getAck() << "\n";
				break;
			case Category::Def:
				cout << "   방어력 상승 : " << inventory[i].getDef() << "\n";
				break;
			case Category::Hp:
				cout << "   체력 상승 : " << inventory[i].getHp() << "\n";
				break;
			}
			cout << endl;
		}
	}
};

// 아이템 설명 함수 (아이템의 카테고리에 맞게 설명을 출력)
void ItemExp(Item& item, int index) {
	cout << index << ". " << item.getItemName() << " (" << item.getPrice() << "G)" << endl;
	cout << "   " << item.getExplanation() << "\n";

	// 카테고리에 맞는 아이템의 스탯 정보도 출력
	switch (item.getCategory()) {
	case Category::Ack:
		cout << "   공격력 상승 : " << item.getAck() << "\n";
		break;
	case Category::Def:
		cout << "   방어력 상승 : " << item.getDef() << "\n";
		break;
	case Category::Hp:
		cout << "   체력 상승 : " << item.getHp() << "\n";
		break;
	}
	cout << "\n";
}

int main()
{
	//player 객체 생성
	Player player;
	//아이템 객체 생성 및 설정
	vector<Item> shoplist;
	shoplist.push_back(Item("롱소드", 15, 0, 0, 450, "기본적인 검이다", Category::Ack));
	shoplist.push_back(Item("천갑옷", 0, 10, 0, 450, "얇은 갑옷이다", Category::Def));
	shoplist.push_back(Item("여신의 눈물", 0, 0, 300, 800, "희미하게 푸른빛을 품고 있는 보석이다", Category::Hp));

	cout << "**************************" << "\n";
	cout << "*******아이템 상점********" << "\n";
	cout << "**************************" << "\n";

	while (true) {
		int num;
		cout << endl;
		cout << "======= 상점 메뉴 =======" << "\n";
		cout << "1.아이템 구매" << "\n";
		cout << "2.아이템 판매" << "\n";
		cout << "3.아이템 확인" << "\n";
		cout << "메뉴를 선택하세요 : ";
		cin >> num;

		switch (num)
		{
			//아이템 구매
		case 1:
		{
			cout << "=== 아이템 구매 ===" << "\n";
			cout << "보유한 골드 : " << player.getGold() << "G" << "\n" << "\n";

			for (int i = 0; i < shoplist.size(); i++) {
				ItemExp(shoplist[i], i + 1);
				cout << endl;
			}
			cout << "구매할 아이템을 선택하세요 (취소 0) : ";
			cin >> num;
			if (num == 0)
				cout << "아이템 구매를 취소하셨습니다" << "\n";
			else if (num >= 1 && num <= shoplist.size())
				player.buyItem(shoplist[num - 1]);
			else
				cout << "잘못된 접근입니다" << "\n";
			break;
		}
		//아이템 판매
		case 2:
		{
			cout << "=== 아이템 판매 ===" << "\n";
			player.displayInventory();
			cout << "판매할 아이템을 선택하세요 (취소 0) : ";
			cin >> num;
			if (num == 0)
				cout << "아이템 판매를 취소하셨습니다" << "\n";
			else if (num >= 1 && num <= !player.isInvenEmpty())
				player.sellItem(num - 1);
			else
				cout << "잘못된 접근입니다" << "\n";
			break;
		}
		//아이템 확인
		case 3:
		{
			cout << "=== 아이템 확인 ===" << "\n";
			player.displaystat();
			player.displayInventory();
			cout << "계속하려면 아무키나 입력하세요 : ";
			cin.ignore();  // 버퍼 비우기 (이전 cin에서 남은 개행문자 제거)
			cin.get();     // 사용자 입력 대기
			break;
		}
		default:
			cout << "잘못 입력해서 상점이 폭파했습니다" << endl;
			return 0;
		};
	}
}