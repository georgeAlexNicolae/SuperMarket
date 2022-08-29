#include <iostream> 
#include <vector>
#include <iterator>  
#include <algorithm>
#include <ctime>
#include <string.h>
#include <chrono>
#include <typeinfo>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class ProductAbstract
{
	// Atributele clasei (definite in zona privata)
private:
	int id;
	float price;
	char* name;
	char* description;
	char* unit_of_measure;

public:

	// 2 functii virtuale pure. Vor fi implementate in clasa Product, care mosteneste clasa ProductAbstract
	virtual string get_csv_header_line() = 0;
	virtual string get_csv_line() = 0;

	// Destructor care elibereaza memoria ocupata de pointeri
	~ProductAbstract()
	{
		delete[] name;
		delete[] description;
		delete[] unit_of_measure;
	}

	// Constructor implicit
	ProductAbstract() {}

	// Constructor de copiere 
	ProductAbstract(const ProductAbstract& t)
	{
		id = t.get_id();
		price = t.get_price();
		set_name(t.get_name());
		set_description(t.get_description());
		set_unit_of_measure(t.get_unit_of_measure());
	}

	// Constructor de atribuire
	ProductAbstract& operator=(const ProductAbstract& t)
	{
		return *this;
	}

	// Constructor cu parametri
	ProductAbstract(int id_, float p, char* n, char* d, char* um, int stock)
	{
		id = id_;
		price = p;
		name = new char[sizeof(char) * strlen(n) + 1];
		description = new char[sizeof(char) * strlen(d) + 1];
		unit_of_measure = new char[sizeof(char) * strlen(um) + 1];
		set_name(n);
		set_description(d);
		set_unit_of_measure(um);
	}

	// functii accesor
	void set_id(int id)
	{
		if (id >= 0)
		{
			this->id = id;
		}
		else
		{
			cout << "Incorrect product ID" << endl;
		}
	}

	int get_id() const
	{
		return this->id;
	}

	void set_price(float price)
	{
		this->price = price;
	}

	float get_price() const
	{
		return this->price;
	}

	void set_name(char* name)
	{
		if (name == NULL)
		{
			return;
		}
		this->name = new char[sizeof(char) * (strlen(name) + 1)];

		strcpy_s(this->name, strlen(name) + 1, name);
	}

	char* get_name() const
	{
		return this->name;
	}

	void set_description(char* description)
	{
		if (description == NULL)
		{
			return;
		}
		this->description = new char[sizeof(char) * (strlen(description) + 1)];
		strcpy_s(this->description, strlen(description) + 1, description);
	}

	char* get_description() const
	{
		return this->description;
	}

	void set_unit_of_measure(char* unit_of_measure)
	{
		if (unit_of_measure == NULL)
		{
			return;
		}
		this->unit_of_measure = new char[sizeof(char) * (strlen(unit_of_measure) + 1)];

		strcpy_s(this->unit_of_measure, strlen(unit_of_measure) + 1, unit_of_measure);
	}

	char* get_unit_of_measure()const
	{
		return this->unit_of_measure;
	}

	// Supraincarcata operatorului >>
	friend istream& operator>>(istream& input, ProductAbstract& product)
	{
		char name[100];
		char description[200];
		char um[20];
		float price;
		int id;

		cout << "Numele produsului: ";
		char c = getchar();
		input.getline(name, sizeof(name));
		product.set_name(name);

		cout << "Produs ID: ";
		input >> id;
		product.set_id(id);

		cout << "Pretul produsului: ";
		c = getchar();
		input >> price;
		product.set_price(price);

		cout << "Descriere: ";
		c = getchar();
		input.getline(description, sizeof(description));
		product.set_description(description);

		cout << "Unitate de masura (bucata, KG, litri, etc.): ";
		//c = getchar();
		input.getline(um, sizeof(um));
		product.set_unit_of_measure(um);

		return input;
	}

	// Supraincarcata operatorului <<
	friend ostream& operator<<(ostream& output, const ProductAbstract& product)
	{
		output << "ID: " << product.get_id() << endl;
		output << "Nume: " << product.get_name() << endl;
		output << "Pret: " << product.get_price() << " lei" << endl;
		output << "Descriere: " << product.get_description() << endl;
		output << "Unitate de masura: " << product.get_unit_of_measure() << endl;
		return output;
	}
	 
	// Supraincarcata operatorului ==
	bool operator==(const ProductAbstract& other) const
	{

		// Let's say that 2 products are equal if they have the same name, price 
		if (strcmp(name, other.get_name()) != 0)
		{
			return false;
		}

		if (price != other.price)
		{
			return false;
		}
		return true;
	}

	// Supraincarcata operatorului >
	bool operator > (const ProductAbstract& other) const
	{
		if (price > other.get_price())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Supraincarcata operatorului <
	bool operator < (const ProductAbstract& other) const
	{
		if (price < other.get_price())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};

// Clasa Product mosteneste clasa ProductAbstract
class Product : public ProductAbstract
{

public:
	// Destructor
	~Product()
	{
		// Destructorii sunt chemati in ordine inversa (Product > ProductAbstract) 
	}

	// Constructor fara parametri
	Product() {}

	// Constructor de copiere
	Product(const Product& t)
	{
		set_id(t.get_id());
		set_price(t.get_price());
		set_name(t.get_name());
		set_description(t.get_description());
		set_unit_of_measure(t.get_unit_of_measure());
	}

	// Constructor de atribuire
	Product& operator=(const Product& t)
	{
		return *this;
	}

	// Constructor cu parametri - cheama constructorul clasei parinte ProductAbstract
	Product(int id_, float p, char* n, char* d, char* um, int stock) :ProductAbstract(id_, p, n, d, um, stock)
	{ 
	} 

	// Supraincarcata operatorului >>
	friend istream& operator>>(istream& input, Product& product)
	{

		char name[100];
		char description[200];
		char um[20];
		float price;
		int id; 

		cout << "Numele produsului: ";
		char c = getchar();
		input.getline(name, sizeof(name));
		product.set_name(name);

		cout << "Produs ID: ";
		input >> id;
		product.set_id(id);

		cout << "Pretul produsului: ";
		c = getchar();
		input >> price;
		product.set_price(price);

		cout << "Descriere: ";
		c = getchar();
		input.getline(description, sizeof(description));
		product.set_description(description);

		cout << "Unitate de masura (bucata, KG, litri, etc.): ";
		//c = getchar();
		input.getline(um, sizeof(um));
		product.set_unit_of_measure(um);

		return input;
	}

	// Supraincarcata operatorului <<
	friend ostream& operator<<(ostream& output, const Product& product)
	{
		output << "ID: " << product.get_id() << endl;
		output << "Nume: " << product.get_name() << endl;
		output << "Pret: " << product.get_price() << " lei" << endl;
		output << "Descriere: " << product.get_description() << endl;
		output << "Unitate de masura: " << product.get_unit_of_measure() << endl;
		return output;
	}

	// Supraincarcata operatorului ++
	Product operator ++ ()
	{
		Product temp;
		// temp.qty_in_stock = ++qty_in_stock;
		return temp;
	}

	// Supraincarcata operatorului ++
	Product operator ++ (int)
	{
		Product temp;
		//  temp.qty_in_stock = ++qty_in_stock;
		return temp;
	}

	// Supraincarcata operatorului --
	Product operator -- ()
	{
		Product temp;
		//    temp.qty_in_stock = --qty_in_stock;
		return temp;
	}

	// Supraincarcata operatorului --
	Product operator -- (int)
	{
		Product temp;
		//    temp.qty_in_stock = --qty_in_stock;
		return temp;
	}

	// Supraincarcata operatorului ==
	bool operator==(const Product& other) const
	{

		// Let's say that 2 products are equal if they have the same name, price 
		if (strcmp(get_name(), other.get_name()) != 0)
		{
			return false;
		}

		if (get_price() != other.get_price())
		{
			return false;
		}
		return true;
	}

	// Supraincarcata operatorului >
	bool operator > (const Product& other) const
	{
		if (get_price() > other.get_price())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Supraincarcata operatorului <
	bool operator < (const Product& other) const
	{
		if (get_price() < other.get_price())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Functie ce returneaza un string ce va fi scris in CSV (antet)
	string get_csv_header_line()
	{
		string result = "ID,NUME,PRET,DESCRIERE,UNITATE DE MASURA\n";
		return result;
	}

	// Functie ce returneaza un string ce va fi scris in CSV, continand datele produsului
	string get_csv_line()
	{
		string result = to_string(get_id()) + ","
			+ string(get_name()) + ","
			+ to_string(get_price()) + ","
			+ string(get_description()) + ","
			+ string(get_unit_of_measure()) + "\n";
		return result;
	}
};

// Clasa Storehouse contine informatii despre produsele existente in stoc
class Storehouse
{
private:
	char* name;
	char* address;
	float area;
	bool is_empty;
	vector<Product> products;

public:
	Storehouse() {}

	~Storehouse()
	{
		delete[] name;
		delete[] address;
		products.clear();
	}

	Storehouse(char* name, char* address, float area)
	{
		this->area = area;
		is_empty = true;
		set_name(name);
		set_address(address);
	}

	Storehouse(const Storehouse& t)
	{
		set_name(t.get_name());
		set_address(t.get_address());

		for (int i = 0; i < t.get_products().size(); i++)
		{
			add_product(get_product_by_index(i));
		}
	}

	Storehouse& operator=(const Storehouse& t)
	{
		return *this;
	}

	void set_name(char* name)
	{
		this->name = new char[sizeof(char) * (strlen(name) + 1)];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	void empty()
	{
		products.clear();
	}


	char* get_name() const
	{
		return name;
	}


	void set_address(char* address)
	{
		this->address = new char[sizeof(char) * (strlen(address) + 1)];
		strcpy_s(this->address, strlen(address) + 1, address);
	}

	char* get_address() const
	{
		return address;
	}

	void set_area(float area)
	{
		if (area > 0)
		{
			this->area = area;
		}
		else
		{
			cout << "Incorrect storehouse area! " << endl;
		}
	}

	float get_area() const
	{
		return area;
	}

	void set_is_empty(bool is_empty)
	{
		this->is_empty = is_empty;
	}

	bool get_is_empty() const
	{
		return is_empty;
	}

	void add_product()
	{
		Product new_product;
		cin >> new_product;
		products.push_back(new_product);
	}

	void add_product(Product p)
	{
		products.push_back(p);
	}


	vector<Product> get_products() const
	{
		return products;
	}

	Product get_product_by_id(int id) const
	{

		bool found = false;
		int i = 0;

		for (i = 0; i < products.size(); i++)
		{
			if (products[i].get_id() == id)
			{
				found = true;
				break;
			}
		}

		if (found)
		{
			return products[i];
		}
		else
		{
			Product dummy;
			return dummy;
		}
	}


	Product get_product_by_index(int id) const
	{
		if (id >= 0 && id < products.size())
			return products[id];
		else
		{
			Product dummy;
			return dummy;
		}
	}

	bool id_exists(int id)
	{
		for (int i = 0; i < products.size(); i++)
		{

			if (products[i].get_id() == id)
			{
				return true;
			}
		}

		return false;
	}


	void delete_product(int id)
	{
		bool found = false;
		unsigned int i = 0;
		vector<Product> products_new;


		for (i = 0; i < products.size(); i++)
		{

			if (products[i].get_id() != id)
			{
				products_new.push_back(products[i]);
			}
			else
			{
				found = true;
			}
		}
		products.clear();
		products = products_new;

		if (found)
		{
			cout << "\nPRODUSUL A FOST STERS!\n" << endl;
		}
		else
		{
			cout << "\nPRODUSUL  NU EXISTA!\n" << endl;
		}
	}

	int get_products_stock() const
	{
		return products.size();
	}

	friend istream& operator>>(istream& input, Storehouse& storehouse)
	{
		char name[100];
		char address[100];
		float area;


		cout << "Enter storehouse name: ";
		char c = getchar();
		input.getline(name, sizeof(name));
		storehouse.set_name(name);

		cout << "Enter storehouse address: ";
		input.getline(address, sizeof(address));
		storehouse.set_address(address);

		cout << "Enter storehouse area (m2): ";
		input >> area;
		storehouse.set_area(area);

		return input;
	}


	friend ostream& operator<<(ostream& output, const Storehouse& storehouse)
	{

		output << "Name: " << storehouse.get_name() << endl;
		output << "Address: " << storehouse.get_address() << endl;
		output << "Area: " << storehouse.get_area() << endl;
		output << "Is empty: " << storehouse.get_is_empty() << endl;
		output << "Products in stock: " << storehouse.get_products_stock() << endl;
		return output;
	}

	Storehouse operator ++ ()
	{
		Storehouse temp;
		temp.set_area(temp.get_area() + 1);
		return temp;
	}

	Storehouse operator ++ (int)
	{
		Storehouse temp;
		temp.set_area(temp.get_area() + 1);
		return temp;
	}

	Storehouse operator -- ()
	{
		Storehouse temp;
		temp.set_area(temp.get_area() - 1);
		return temp;
	}

	Storehouse operator -- (int)
	{
		Storehouse temp;
		temp.set_area(temp.get_area() - 1);
		return temp;
	}

	bool operator==(const Storehouse& other) const
	{
		// Let's say that 2 storehouses are equal if they have the same address
		if (strcmp(get_address(), other.get_address()) != 0)
		{
			return false;
		}

		return true;
	}

	bool operator > (const Storehouse& other) const
	{
		// Compare areas
		if (get_area() > other.get_area())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator < (const Storehouse& other) const
	{
		// Compare areas
		if (get_area() < other.get_area())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// Clasa Purchase contine informatii despre o comanda efectuata de client
class Purchase
{
private:
	vector<Product> products;
	string date_time;
	float amount;
	int products_count;

public:
	Purchase() {}
	~Purchase()
	{
		products.clear();
	}

	Purchase(vector<Product> products, float amount, int products_count)
	{
		for (int i = 0; i < products.size(); i++)
			this->products.push_back(products[i]);
		this->amount = amount;
		this->date_time = current_date_time();
		this->products_count = products_count;
	}

	void set_products(vector<Product> products)
	{
		for (int i = 0; i < products.size(); i++)
			this->products.push_back(products[i]);
	}

	Purchase(const Purchase& t)
	{
		set_date_time(t.get_date_time());
		set_amount(t.get_amount());
		set_products_count(t.get_products_count());
		for (int i = 0; i < t.get_products().size(); i++)
		{
			add_product(t.get_product_by_index(i));
		}
	}


	string get_csv_header_line()
	{
		string result = "DATA,TOTAL,TOTAL PRODUSE\n";
		return result;
	}

	string get_csv_line()
	{
		string result = get_date_time() + ","
			+ to_string(get_amount()) + ","
			+ to_string(get_products_count()) + "\n";
		return result;
	}


	Purchase& operator=(const Purchase& t)
	{
		return *this;
	}

	void add_product(Product product)
	{
		products.push_back(product);
	}

	void set_products_count(int n)
	{
		products_count = n;
	}

	int get_products_count()
	{
		return products_count;
	}

	vector<Product> get_products() const
	{
		return products;
	}

	string get_date_time() const
	{

		return date_time;
	}

	string current_date_time() {
		auto start = std::chrono::system_clock::now();
		auto legacyStart = std::chrono::system_clock::to_time_t(start);
		char tmBuff[30];
		ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
		for (int i = 0; i < 30; i++)
		{
			if (tmBuff[i] == '\n')
			{
				tmBuff[i] = ' ';
			}
		}
		//std::cout << tmBuff << '\n';
		return tmBuff;
	}


	void set_date_time(string dt)
	{
		date_time = dt;
	}

	void set_date_time()
	{
		date_time = current_date_time();
	}

	void set_amount(float amount)
	{
		this->amount = amount;
	}

	float get_amount() const
	{
		return amount;
	}

	int get_products_count() const
	{
		return products_count;
	}

	Product get_product_by_index(int id) const
	{
		if (id >= 0 && id < products.size())
			return products[id];
		else
		{
			Product c;
			return c;
		}
	}


	friend ostream& operator<<(ostream& output, const Purchase& purchase)
	{

		output << "DATA: " << purchase.get_date_time() << endl;
		output << "TOTAL: " << purchase.get_amount() << " lei." << endl;
		output << "TOTAL PRODUSE: " << purchase.get_products_count() << endl;
		output << "-------------------------------- " << endl;
		return output;
	}

	Purchase operator ++ ()
	{
		Purchase temp;
		temp.set_amount(temp.get_amount() + 1);
		return temp;
	}

	Purchase operator ++ (int)
	{
		Purchase temp;
		temp.set_amount(temp.get_amount() + 1);
		return temp;
	}

	Purchase operator -- ()
	{
		Purchase temp;
		temp.set_amount(temp.get_amount() - 1);
		return temp;
	}

	Purchase operator -- (int)
	{
		Purchase temp;
		temp.set_amount(temp.get_amount() - 1);
		return temp;
	}

	bool operator==(const Purchase& other) const
	{
		// Let's say that 2 Purchases are equal if they have the amount
		if (get_amount() != other.get_amount())
		{
			return false;
		}

		return true;
	}

	bool operator > (const Purchase& other) const
	{
		// Compare amount
		if (get_amount() > other.get_amount())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator < (const Purchase& other) const
	{
		// Compare amount
		if (get_amount() < other.get_amount())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Product& operator[](int index)
	{
		if (index >= products.size() || index < 0) {
			cout << "Array index out of bound, exiting";
			exit(0);
		}
		return products[index];
	}

};

// Clasa ShoppingBasket contine informatii despre produsele alese de client pentru a fi cumparate.
class ShoppingBasket
{
private:
	vector<Product> products;
	float total;

public:
	ShoppingBasket() {}
	~ShoppingBasket()
	{
		products.clear();
	}

	ShoppingBasket(vector<Product> products, float amount)
	{
		for (int i = 0; i < products.size(); i++)
		{
			this->products.push_back(products[i]);
		}
		this->total = amount;
	}

	ShoppingBasket(const ShoppingBasket& t)
	{
		for (int i = 0; i < t.get_products().size(); i++)
		{
			add_product(t.get_product_by_index(i));
		}
	}

	Product get_product_by_index(int id) const
	{
		if (id >= 0 && id < products.size())
			return products[id];
		else
		{
			Product c;
			return c;
		}
	}

	ShoppingBasket& operator=(const ShoppingBasket& t)
	{
		return *this;
	}

	void add_product(Product product)
	{
		products.push_back(product);
	}



	vector<Product> get_products() const
	{
		return products;
	}

	float get_total() const
	{
		return total;
	}

	void empty()
	{
		products.clear();
		set_total(0);
	}

	void set_total(float total)
	{
		if (total >= 0)
		{
			this->total = total;
		}
	}

	int get_products_count() const
	{
		return products.size();
	}

	friend ostream& operator<<(ostream& output, const ShoppingBasket& basket)
	{

		output << "Total: " << basket.get_total() << " lei" << endl;
		output << "Products count: " << basket.get_products_count() << endl;

		for (int i = 0; i < basket.get_products().size(); i++)
		{
			output << basket.get_product_by_index(i);
		}
		return output;
	}

	ShoppingBasket operator ++ ()
	{
		//ShoppingBasket temp;
		//temp.set_amount(temp.get_amount() + 1);
		//return temp;
	}

	ShoppingBasket operator ++ (int)
	{
		//ShoppingBasket temp;
		//temp.set_amount(temp.get_amount() + 1);
		//return temp;
	}

	ShoppingBasket operator -- ()
	{
		//ShoppingBasket temp;
		//temp.set_amount(temp.get_amount() - 1);
		//return temp;
	}

	Purchase operator -- (int)
	{
		//ShoppingBasket temp;
		//temp.set_amount(temp.get_amount() - 1);
		//return temp;
	}

	bool operator==(const ShoppingBasket& other) const
	{
		// Let's say that 2 ShoppingBasket are equal if they have the total
		if (get_total() != other.get_total())
		{
			return false;
		}

		return true;
	}

	bool operator > (const ShoppingBasket& other) const
	{
		// Compare amount
		if (get_total() > other.get_total())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator < (const ShoppingBasket& other) const
	{
		// Compare amount
		if (get_total() < other.get_total())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Product& operator[](int index)
	{
		if (index >= products.size() || index < 0) {
			cout << "Array index out of bound, exiting";
			//exit(0);
		}
		return products[index];
	}
};

// Clasa Supermarket gestioneaza toate celelate clase/metode. 
// Punctul de start este metoda start().
class Supermarket
{
private:
	vector<Purchase> purchases;
	Storehouse storehouse;
	ShoppingBasket basket;
	bool first_calling;
	const string NAME = "LIDL";
	vector<int> sell_count;

public:
	// Constructor fara parametri
	Supermarket()
	{
		first_calling = true;
	}
	~Supermarket()
	{
	}

	// Constructor cu parametri
	Supermarket(vector<Purchase> p, Storehouse s)
	{
		for (int i = 0; i < p.size(); i++)
		{
			purchases.push_back(p[i]);
		}
		storehouse = s;
	}

	// Constructor de copiere
	Supermarket(const Supermarket& s)
	{
		vector<Purchase> pp = s.get_purchases();
		for (int i = 0; i < pp.size(); i++)
		{
			add_purchase(pp[i]);
		}
		storehouse = s.get_storehouse();
	}

	// Constructor de atribuire
	Supermarket& operator=(const Supermarket& t)
	{
		return *this;
	}

	// Functii accesor
	Storehouse get_storehouse() const
	{
		return storehouse;
	}

	vector<Purchase> get_purchases() const
	{
		return purchases;
	}

	void add_purchase(Purchase p)
	{
		purchases.push_back(p);
	}

	void display_main_menu()
	{
		cout << "       BUN VENIT LA " << NAME << "!" << endl;
		cout << "==================================" << endl;
		cout << "1. Sunt administrator" << endl;
		cout << "2. Sunt cumparator" << endl;
		cout << "==================================" << endl;
	}

	void display_admin_menu()
	{
		cout << "       PANOUL ADMINISTRATORULUI" << endl;
		cout << "==================================" << endl;
		cout << "1. Gestionare comenzi " << endl;
		cout << "2. Gestionare produse" << endl; 
		cout << "3. Inapoi" << endl;
		cout << "0. Iesi din aplicatie" << endl;
		cout << "==================================" << endl;
	}

	void display_customer_menu()
	{
		cout << "       PANOUL CUMPARATORULUI" << endl;
		cout << "==================================" << endl;
		cout << "1. Vezi cosul de cumparaturi " << endl;
		cout << "2. Alege produse" << endl;
		cout << "3. Inapoi" << endl;
		cout << "0. Iesi din aplicatie" << endl;
		cout << "==================================" << endl;
	}

	void maintain_products_menu()
	{
		cout << "       GESTIONARE PRODUSE" << endl;
		cout << "==================================" << endl;
		cout << "1. Adauga un produs nou" << endl;
		cout << "2. Cauta un produs dupa ID" << endl;
		cout << "3. Sterge un produs dupa ID" << endl;
		// cout << "4. Modifica un produs dupa ID" << endl;
		cout << "5. Afiseaza toate produsele" << endl;
		cout << "6. Salveaza produsele in CSV" << endl;
		cout << "7. Citeste produsele din CSV" << endl;
		cout << "0. Mergi la meniul principal" << endl;
		cout << "==================================" << endl;
	}

	void display_product()
	{
		cout << "       CAUTARE PRODUS DUPA ID" << endl;
		cout << "==================================" << endl;
		int id;

		cout << " > introdu ID-ul produsului: ";
		cin >> id;

		Product product = storehouse.get_product_by_id(id);

		if (product.get_name() == NULL)
		{
			cout << "\nProdusul cu ID " << id << " nu a fost gasit!" << endl << endl;
		}
		else
		{
			cout << product;
		}

	}

	void delete_product_by_id()
	{
		cout << "       STERGERE PRODUS" << endl;
		cout << "==================================" << endl;
		int id;

		cout << " > introduceti ID-ul produsului: ";
		cin >> id;

		storehouse.delete_product(id);

	}

	void maintain_products()
	{
		bool exit = false;
		int user_choice;

		clear_screen();

		while (true)
		{
			maintain_products_menu();
			cout << "Alege o optiune: ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:
				clear_screen();
				add_product();
				break;
			case 2:
				clear_screen();
				display_product();
				break;
			case 3:
				clear_screen();
				delete_product_by_id();
				break;
			case 4:
				clear_screen();
				break;
			case 5:
				clear_screen();
				view_all_products();
				break;
			case 6:
				clear_screen();
				write_csv_products();
				break;
			case 7:
				clear_screen();
				read_csv_products(false);
				break;
			case 0:
				exit = true;
				break;
			default:
				cout << "Optiune incorecta! Alege alta.";
				break;
			}
			if (exit)
			{
				break;
			}
		}
	}

	void maintain_purchases()
	{
		bool exit = false;
		int user_choice;

		clear_screen();

		while (true)
		{
			maintain_purchases_menu();
			cout << "Alege o optiune: ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:
				clear_screen();
				display_purchases();
				break;
			case 2:
				clear_screen();
				write_csv_purchases();
				break;
			case 3:
				clear_screen();
				read_csv_purchases(false);
				// delete_product_by_id();
				break;
			case 0:
				exit = true;
				break;
			default:
				cout << "Optiune incorecta! Alege alta.";
				break;
			}
			if (exit)
			{
				break;
			}
		}
	}

	void maintain_purchases_menu()
	{
		cout << "       GESTIONARE COMENZI" << endl;
		cout << "==================================" << endl;
		cout << "1. Afiseaza toate comenzile" << endl;
		cout << "2. Salveaza comenzile in CSV" << endl;
		cout << "3. Citeste comenzile din CSV" << endl;
		cout << "0. Mergi la meniul principal" << endl;
		cout << "==================================" << endl;
	}

	void display_purchases()
	{

		cout << "       ISTORIA COMENZILOR" << endl;
		cout << "==================================" << endl;

		if (purchases.size() == 0)
		{
			cout << "Nu exista comenzi." << endl;
		}
		else
		{
			for (int i = 0; i < purchases.size(); i++)
			{
				cout << purchases[i];
			}
		}

		cout << "==================================" << endl;
	}

	void add_product()
	{
		cout << "     ADAUGARE PRODUS NOU: " << endl;
		cout << "==================================" << endl;
		storehouse.add_product();
		clear_screen();
		cout << "\n     PRODUS ADAUGAT CU SUCCESS! " << endl;
	}

	void read_csv_products(bool called_from_start)
	{
		ifstream csv_file;
		csv_file.open("produse.csv");

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		if (csv_file.is_open())
		{
			while (getline(csv_file, line))
			{
				row.clear();
				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else
		{
			if (!called_from_start)
			{
				cout << "Nu exista fisier CSV produse.csv\n";
			}
			return;
		}


		if (content.size() > 0)
		{
			storehouse.empty();
		}

		for (int i = 1; i < content.size(); i++)
		{
			Product new_product;

			stringstream stream_id(content[i][0]);
			int id = 0;
			stream_id >> id;
			new_product.set_id(id);

			size_t size_ = content[i][1].length();

			char* name;
			name = &content[i][1][0];
			new_product.set_name(name);

			stringstream stream_price(content[i][2]);
			float price = 0;
			stream_price >> price;
			new_product.set_price(price);

			char* description;
			description = &content[i][3][0];
			new_product.set_description(description);

			char* um;
			um = &content[i][4][0];
			new_product.set_unit_of_measure(um);

			storehouse.add_product(new_product);
		}

		if (!called_from_start)
		{
			cout << "DATELE AU FOST CITITE DIN CSV CU SUCCES!" << endl << endl;
		}

		csv_file.close();
	}

	void read_csv_purchases(bool called_from_start)
	{
		ifstream csv_file;
		csv_file.open("comenzi.csv");

		vector<vector<string>> content;
		vector<string> row;
		string line, word;

		if (csv_file.is_open())
		{
			while (getline(csv_file, line))
			{
				row.clear();
				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				content.push_back(row);
			}
		}
		else
		{
			if (!called_from_start)
			{
				cout << "Nu exista fisier CSV comenzi.csv\n";
			}
			return;
		}


		if (content.size() > 0)
		{
			purchases.clear();
		}

		for (int i = 1; i < content.size(); i++)
		{
			Purchase new_purchase;
			new_purchase.set_date_time(content[i][0]);

			stringstream stream_amount(content[i][1]);
			float amount = 0;
			stream_amount >> amount;
			new_purchase.set_amount(amount);

			stringstream stream_count(content[i][2]);
			int count = 0;
			stream_count >> count;
			new_purchase.set_products_count(count);

			purchases.push_back(new_purchase);
		}

		if (!called_from_start)
		{
			cout << "DATELE AU FOST CITITE DIN CSV CU SUCCES!" << endl << endl;
		}

		csv_file.close();
	}

	void write_csv_products()
	{
		clear_screen();
		cout << "       SCRIERE PRODUSE IN CSV" << endl;
		cout << "==================================" << endl;
		ofstream csv_file;

		string file_path;

		cout << "Introduceti calea + numele fisierul CSV.";
		cout << "(tastati + pentru a salva implicit in folderul actual)" << endl;
		cout << " > alegerea dvs: ";
		cin >> file_path;

		if (file_path == "+")
		{
			csv_file.open("produse.csv");
		}
		else
		{
			csv_file.open(file_path);
		}

		vector<Product> products = storehouse.get_products();

		if ((products.size()) == 0)
		{
			cout << "Nu sunt produse!" << endl;
			return;
		}
		else
		{
			for (int i = 0; i < products.size(); i++)
			{
				if (i == 0)
				{
					csv_file << products[i].get_csv_header_line();
				}
				csv_file << products[i].get_csv_line();
			}

			csv_file.close();
			cout << "\nDATELE AU FOST SCRISE IN CSV CU SUCCES!" << endl << endl;
		}
	}

	void write_csv_purchases()
	{
		clear_screen();
		cout << "       SCRIERE COMENZI IN CSV" << endl;
		cout << "==================================" << endl;
		ofstream csv_file;

		string file_path;

		cout << "Introduceti calea + numele fisierul CSV.";
		cout << "(tastati + pentru a salva implicit in folderul actual)" << endl;
		cout << " > alegerea dvs: ";
		cin >> file_path;

		if (file_path == "+")
		{
			csv_file.open("comenzi.csv");
		}
		else
		{
			csv_file.open(file_path);
		}

		if ((purchases.size()) == 0)
		{
			cout << "Nu sunt comenzi!" << endl;
			return;
		}
		else
		{
			for (int i = 0; i < purchases.size(); i++)
			{
				if (i == 0)
				{
					csv_file << purchases[i].get_csv_header_line();
				}
				csv_file << purchases[i].get_csv_line();
			}

			csv_file.close();
			cout << "\nDATELE AU FOST SCRISE IN CSV CU SUCCES!" << endl << endl;
		}
	}

	void view_all_products()
	{
		vector<Product> products = storehouse.get_products();
		cout << "     LISTA DE PRODUSE (" << products.size() << "):" << endl;
		cout << "==================================" << endl;

		if (products.size() == 0)
		{
			cout << "Nu sunt produse in stock" << endl;
		}
		else
		{
			for (int i = 0; i < products.size(); i++)
			{
				cout << products[i] << endl;
			}
		}
		cout << "==================================" << endl;

	}

	void admin()
	{
		bool exit = false;
		int user_choice;

		clear_screen();

		while (true)
		{
			display_admin_menu();
			cout << "Alege o optiune: ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:
				clear_screen();
				maintain_purchases();
				break;
			case 2:
				clear_screen();
				maintain_products();
				break;
			case 3:
				clear_screen();
				start(); 
				break; 
			case 0:
				exit = true;
				break;
			default:
				cout << "Optiune incorecta! Alege alta.";
				break;
			}
			if (exit)
			{
				break;
			}
		}
	}

	void show_basket()
	{
		int user_choice = 0;
		bool exit = false;

		vector<Product> products = basket.get_products();
		cout << "       COSUL DE CUMPARATURI (" << products.size() << ")" << endl;
		cout << "==================================" << endl;


		if (products.size() > 0)
		{
			for (int i = 0; i < products.size(); i++)
			{
				cout << products[i] << endl;
			}
		}
		else
		{
			cout << " Nu sunt produse in cos." << endl;
		}

		cout << "==================================" << endl;

		cout << "TOTAL: " << basket.get_total() << " lei." << endl << endl;

		while (true)
		{
			cout << "1. Goleste cosul " << endl;
			cout << "2. Achitare" << endl;
			cout << "0. Inapoi la produse" << endl << endl << endl;

			cout << " > alege o optiune: ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:
				clear_screen();
				basket.empty();
				cout << "COSUL A FOST GOLIT" << endl << endl;
				customer();
				exit = true;
				break;
			case 2:
				clear_screen();
				payment();
				basket.empty();
				customer();
				exit = true;
				break;
			case 0:
				clear_screen();
				exit = true;
				break;
			default:
				cout << endl << "Optiune gresita! " << endl << endl;
				break;
			}

			if (exit)
			{
				break;
			}
		}
	}

	void payment()
	{
		if (basket.get_products().size() == 0)
		{
			cout << "NU AVETI NICIUN PRODUS IN COS PENTRU A ACHITA! " << endl << endl;
			return;
		}

		Purchase purchase;
		purchase.set_products(basket.get_products());
		purchase.set_date_time();
		purchase.set_amount(basket.get_total());
		purchase.set_products_count(basket.get_products().size());
		purchases.push_back(purchase);
		cout << "MULTUMIM PENTRU CUMPARATURI! VA MAI ASTEPTAM! \n" << endl;
	}

	void explore_products()
	{
		int user_choice;
		bool exit;

		vector<Product> products = storehouse.get_products();

		if (products.size() == 0)
		{
			cout << "       TOATE PRODUSELE (" << products.size() << ")" << endl;
			cout << "==================================" << endl;
			cout << "Nu sunt produse." << endl;
			cout << "==================================" << endl;
		}
		else
		{ 
			while (true)
			{
				cout << "       TOATE PRODUSELE (" << products.size() << ")" << endl;
				cout << "==================================" << endl;
				for (int i = 0; i < products.size(); i++)
				{
					cout << products[i] << endl;
				}
				cout << "==================================" << endl << endl;

				cout << " > alegeti un produs dupa ID: ";
				cin >> user_choice;

				Product product = storehouse.get_product_by_id(user_choice);
				if (product.get_name() == NULL)
				{
					cout << "Produs cu ID incorect! " << endl;
				}
				else
				{
					basket.add_product(product);
					basket.set_total(basket.get_total() + product.get_price());

					cout << endl << "Produsul a fost adaugat in cos! " << endl << endl;

					cout << "1. Alegeti alt produs" << endl;
					cout << "2. Mergeti la cosul de cumparaturi" << endl;
					cout << "0. INAPOI" << endl;
					cin >> user_choice;

					switch (user_choice)
					{
					case 1:
						clear_screen();
						break;
					case 2:
						clear_screen();
						show_basket();
						break;
					case 3:
						exit = true;
						break;

					default:
						cout << "Optiune incorecta!" << endl;
						break;
					}
				}
			}
		}
	}

	void customer()
	{
		bool exit = false;
		int user_choice;

		while (true)
		{
			display_customer_menu();

			cout << "Alege o optiune: ";
			cin >> user_choice;

			switch (user_choice)
			{
			case 1:
				clear_screen();
				show_basket();
				break;
			case 2:
				clear_screen();
				explore_products();
				break;
			case 3:
				clear_screen();
				start();
				break;
			case 0:
				exit = true;
				break;
			default:
				cout << "Optiune incorecta! Alege alta.";
				break;
			}
			if (exit)
			{
				break;
			}
		}
	}

	void start()
	{
		int user_choice = 0;
		bool exit = false;

		if (first_calling)
		{
			read_csv_products(true);
			read_csv_purchases(true);
			first_calling = false;
		}

		display_main_menu();
		cout << "Alege o optiune: ";
		cin >> user_choice;

		switch (user_choice)
		{
		case 1:
			admin();
			break;
		case 2:
			clear_screen();
			customer();
			break;
		default:
			cout << "Optiune incorecta!";
			break;
		}
	}

	void clear_screen()
	{
		system("@cls||clear");
	}
};

int main()
{
	Supermarket supermarket;
	supermarket.start();
	return 0;
}