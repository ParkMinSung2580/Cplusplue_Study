#include <iostream>
#include <vector>
using namespace std;

enum class Category {
	Ack = 1,  //����
	Def = 2,  //���
	Hp = 3    //ü��
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
	//���� �����ϸ� ���ϰ� -1
	bool buyItem(Item item) {
		// ��尡 ������� üũ
		if (playerGold < item.getPrice()) {
			cout << "��尡 �����մϴ�!" << endl;
			return false;
		}

		// �κ��丮�� �� á���� üũ
		if (isInvenFull()) {
			cout << "�κ��丮�� ���� á���ϴ�!" << endl;
			return false;
		}

		// ���� ����
		inventory.push_back(item);
		playerAck += item.getAck();
		playerDef += item.getDef();
		playerHp += item.getHp();
		playerGold -= item.getPrice();

		cout << item.getItemName() << "�� �����߽��ϴ�." << endl;

		switch (item.getCategory()) {
		case Category::Ack:
			cout << "�÷��̾��� ���ݷ��� " << item.getAck() << " ����Ͽ� " << playerAck << "�� �˴ϴ�." << "\n";
			break;
		case Category::Def:
			cout << "�÷��̾��� ������ " << item.getDef() << " ����Ͽ� " << playerDef << "�� �˴ϴ�." << "\n";
			break;
		case Category::Hp:
			cout << "�÷��̾��� ü���� " << item.getHp() << " ����Ͽ� " << playerHp << "�� �˴ϴ�." << "\n";
			break;
		}
		cout << "������ ��尡 " << item.getPrice() << "G �����Ͽ� " << playerGold << "G�� �˴ϴ�." << "\n";

		return true;
	}
	//�Ǹ� �Ұ��� -1 ����
	bool sellItem(int index) {
		// �κ��丮�� ����ų� �߸��� �ε����� ���
		if (inventory.empty() || index < 0 || index >= inventory.size()) {
			cout << "��ȿ���� ���� �������Դϴ�." << endl;
			return false;
		}

		Item item = inventory[index];

		playerAck -= item.getAck();
		playerDef -= item.getDef();
		playerHp -= item.getHp();
		playerGold += item.getPrice();

		inventory.erase(inventory.begin() + index);
		cout << item.getItemName() << "���Ǹ��մϴ�" << "\n";

		switch (item.getCategory()) {
		case Category::Ack:
			cout << "�÷��̾��� ���ݷ��� " << item.getAck() << " �϶��Ͽ� " << playerAck << "�� �˴ϴ�." << "\n";
			break;
		case Category::Def:
			cout << "�÷��̾��� ������ " << item.getDef() << " �϶��Ͽ� " << playerDef << "�� �˴ϴ�." << "\n";
			break;
		case Category::Hp:
			cout << "�÷��̾��� ü���� " << item.getHp() << " �϶��Ͽ� " << playerHp << "�� �˴ϴ�." << "\n";
			break;
		}
		cout << "������ ��尡 " << item.getPrice() << "G ����Ͽ� " << playerGold << "G�� �˴ϴ�." << "\n";
		cout << endl;
		return true;
	}

	void displaystat()
	{
		cout << "\n";
		cout << "�÷��̾� ��� ������ : " << playerGold << "G\n";
		cout << "�÷��̾� ���ݷ� ��·� : " << playerAck << "\n";
		cout << "�÷��̾� ���� ��·� : " << playerDef << "\n";
		cout << "�÷��̾� ü�� ��·� : " << playerHp << "\n";
		cout << "\n";
	}

	void displayInventory()
	{
		if (inventory.empty()) {
			cout << "�κ��丮�� ����ֽ��ϴ�." << endl;
			return;
		}

		for (int i = 0; i < inventory.size(); i++)
		{
			cout << i + 1 << ".  " << inventory[i].getItemName() << "\n";
			cout << "  ���� : " << inventory[i].getPrice() << "G" << "\n";
			cout << "  ���� : " << inventory[i].getExplanation() << "\n";
			switch (inventory[i].getCategory())
			{
			case Category::Ack:
				cout << "   ���ݷ� ��� : " << inventory[i].getAck() << "\n";
				break;
			case Category::Def:
				cout << "   ���� ��� : " << inventory[i].getDef() << "\n";
				break;
			case Category::Hp:
				cout << "   ü�� ��� : " << inventory[i].getHp() << "\n";
				break;
			}
			cout << endl;
		}
	}
};

// ������ ���� �Լ� (�������� ī�װ��� �°� ������ ���)
void ItemExp(Item& item, int index) {
	cout << index << ". " << item.getItemName() << " (" << item.getPrice() << "G)" << endl;
	cout << "   " << item.getExplanation() << "\n";

	// ī�װ��� �´� �������� ���� ������ ���
	switch (item.getCategory()) {
	case Category::Ack:
		cout << "   ���ݷ� ��� : " << item.getAck() << "\n";
		break;
	case Category::Def:
		cout << "   ���� ��� : " << item.getDef() << "\n";
		break;
	case Category::Hp:
		cout << "   ü�� ��� : " << item.getHp() << "\n";
		break;
	}
	cout << "\n";
}

int main()
{
	//player ��ü ����
	Player player;
	//������ ��ü ���� �� ����
	vector<Item> shoplist;
	shoplist.push_back(Item("�ռҵ�", 15, 0, 0, 450, "�⺻���� ���̴�", Category::Ack));
	shoplist.push_back(Item("õ����", 0, 10, 0, 450, "���� �����̴�", Category::Def));
	shoplist.push_back(Item("������ ����", 0, 0, 300, 800, "����ϰ� Ǫ������ ǰ�� �ִ� �����̴�", Category::Hp));

	cout << "**************************" << "\n";
	cout << "*******������ ����********" << "\n";
	cout << "**************************" << "\n";

	while (true) {
		int num;
		cout << endl;
		cout << "======= ���� �޴� =======" << "\n";
		cout << "1.������ ����" << "\n";
		cout << "2.������ �Ǹ�" << "\n";
		cout << "3.������ Ȯ��" << "\n";
		cout << "�޴��� �����ϼ��� : ";
		cin >> num;

		switch (num)
		{
			//������ ����
		case 1:
		{
			cout << "=== ������ ���� ===" << "\n";
			cout << "������ ��� : " << player.getGold() << "G" << "\n" << "\n";

			for (int i = 0; i < shoplist.size(); i++) {
				ItemExp(shoplist[i], i + 1);
				cout << endl;
			}
			cout << "������ �������� �����ϼ��� (��� 0) : ";
			cin >> num;
			if (num == 0)
				cout << "������ ���Ÿ� ����ϼ̽��ϴ�" << "\n";
			else if (num >= 1 && num <= shoplist.size())
				player.buyItem(shoplist[num - 1]);
			else
				cout << "�߸��� �����Դϴ�" << "\n";
			break;
		}
		//������ �Ǹ�
		case 2:
		{
			cout << "=== ������ �Ǹ� ===" << "\n";
			player.displayInventory();
			cout << "�Ǹ��� �������� �����ϼ��� (��� 0) : ";
			cin >> num;
			if (num == 0)
				cout << "������ �ǸŸ� ����ϼ̽��ϴ�" << "\n";
			else if (num >= 1 && num <= !player.isInvenEmpty())
				player.sellItem(num - 1);
			else
				cout << "�߸��� �����Դϴ�" << "\n";
			break;
		}
		//������ Ȯ��
		case 3:
		{
			cout << "=== ������ Ȯ�� ===" << "\n";
			player.displaystat();
			player.displayInventory();
			cout << "����Ϸ��� �ƹ�Ű�� �Է��ϼ��� : ";
			cin.ignore();  // ���� ���� (���� cin���� ���� ���๮�� ����)
			cin.get();     // ����� �Է� ���
			break;
		}
		default:
			cout << "�߸� �Է��ؼ� ������ �����߽��ϴ�" << endl;
			return 0;
		};
	}
}