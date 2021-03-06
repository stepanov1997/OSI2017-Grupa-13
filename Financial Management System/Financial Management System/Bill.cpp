#include "Bill.h"
#include "Account.h"
#include "Interface.h"

Bill::Bill(): nameOfBill(nullptr),nameOfClient(nullptr), date(Date(0,0,0))
{}

Bill::Bill(const std::string &inputFileName,int formatCode):nameOfBill(inputFileName),formatCode(formatCode)
{
	process();
}

void Bill::process()
{
	if (formatCode == isFormat[0])
		processFormat1();
	else if (formatCode == isFormat[1])
		processFormat2();
	else if (formatCode == isFormat[2])
		processFormat3();
	else if (formatCode == isFormat[3])
		processFormat4();
	else processFormat5();
}

void Bill::processFormat1()
{
	std::ifstream inputf(nameOfBill);
	std::string tmp;
	inputf.ignore(7);
	getline(inputf, nameOfClient,END_OF_LINE);//pretpostavlja se da se ne stavljaju razmaci poslije naziva

	inputf.ignore(7);
	processDate(inputf);

	for(int i=0;i<4;i++)
	  ignoreElementsUntil(inputf, END_OF_LINE);
	
	getline(inputf,tmp,END_OF_LINE);//
	while (tmp[0] != '-')//radi dok se ne dodlje do linije sa -----------------------------
	{
		Product product = processDataForFormat124(tmp);
		putNewProductInList(product);
		getline(inputf, tmp,END_OF_LINE);
	}
	std::string totalSumOfProducts, pdv, totalSumOfBill;//maskiraju podatke clanove klase Bill

	inputf.ignore(8);
	getline(inputf, totalSumOfProducts,END_OF_LINE);

	inputf.ignore(5);
	getline(inputf, pdv,END_OF_LINE);

	inputf.ignore(20);
	getline(inputf,totalSumOfBill,END_OF_LINE);

	this->totalSumOfProducts = std::stod(totalSumOfProducts, nullptr);
	this->pdv = std::stod(pdv, nullptr);
	this->totalSumOfBill = std::stod(totalSumOfBill, nullptr);
	inputf.close();
}

void Bill::processFormat2() 
{
		std::ifstream inputf(nameOfBill);
		std::string tmp;
		
		for (int i = 0; i<5; i++)
			ignoreElementsUntil(inputf, END_OF_LINE);
		
		inputf.ignore(7);
		getline(inputf, nameOfClient, END_OF_LINE);//pretpostavlja se da se ne stavljaju razmaci poslije naziva

		for (int i = 0; i<3; i++)
			ignoreElementsUntil(inputf, END_OF_LINE);
        
		getline(inputf, tmp, END_OF_LINE);//
		while (tmp[0] != '-')//radi dok se ne dodlje do linije sa -----------------------------
		{
			Product product = processDataForFormat124(tmp);
			putNewProductInList(product);
			getline(inputf, tmp, END_OF_LINE);
		}

		for (int i = 0; i<1; i++)
			ignoreElementsUntil(inputf, END_OF_LINE);
		
		std::string totalSumOfProducts, pdv, totalSumOfBill;//maskiraju podatke clanove klase Bill
		
		inputf.ignore(8);
		getline(inputf, totalSumOfProducts, END_OF_LINE);
		
		inputf.ignore(5);
		getline(inputf, pdv, END_OF_LINE);
		
		inputf.ignore(20);
		getline(inputf, totalSumOfBill, END_OF_LINE);

		inputf.ignore(7);
		processDate(inputf);
        getline(inputf, tmp, END_OF_LINE);//
		
		this->totalSumOfProducts = std::stod(totalSumOfProducts, nullptr);
		this->pdv = std::stod(pdv, nullptr);
		this->totalSumOfBill = std::stod(totalSumOfBill, nullptr);
		inputf.close();
}

void Bill::processFormat3() 
{
		std::ifstream inputf(nameOfBill);
		std::string tmp;

		for (int i = 0; i<2; i++)
			ignoreElementsUntil(inputf, END_OF_LINE);

		inputf.ignore(7);
		getline(inputf, nameOfClient, END_OF_LINE);//pretpostavlja se da se ne stavljaju razmaci poslije naziva

		inputf.ignore(7);
		processDate(inputf);

		for (int i = 0; i<5; i++)
			ignoreElementsUntil(inputf, END_OF_LINE);

		getline(inputf, tmp, END_OF_LINE);//
		while (tmp[0] != '-')//radi dok se ne dodlje do linije sa -----------------------------
		{
			Product product = processDataForFormat3(tmp);
			putNewProductInList(product);
			getline(inputf, tmp, END_OF_LINE);
		}

		ignoreElementsUntil(inputf, END_OF_LINE);

		std::string totalSumOfProducts, pdv, totalSumOfBill;//maskiraju podatke clanove klase Bill
		
		getline(inputf, tmp, END_OF_LINE);
		
		int posTSOP = tmp.find('\t', 8);
		totalSumOfProducts = tmp.substr(8, posTSOP - 8);
		
		while (!std::isalpha(tmp[++posTSOP]));
		posTSOP += 5;
		pdv = tmp.substr(posTSOP);

		ignoreElementsUntil(inputf, END_OF_LINE);

		inputf.ignore(20);
		getline(inputf, totalSumOfBill, END_OF_LINE);

		this->totalSumOfProducts = std::stod(totalSumOfProducts, nullptr);
		this->pdv = std::stod(pdv, nullptr);
		this->totalSumOfBill = std::stod(totalSumOfBill, nullptr);
		inputf.close();
}

void Bill::processFormat4() 
{
	std::ifstream inputf(nameOfBill);
	std::string tmp;
	
	inputf.ignore(7);
	getline(inputf, nameOfClient, END_OF_LINE);//pretpostavlja se da se ne stavljaju razmaci poslije naziva

	inputf.ignore(7);
	processDate(inputf);

	for (int i = 0; i<5; i++)
		ignoreElementsUntil(inputf, END_OF_LINE);

	getline(inputf, tmp, END_OF_LINE);//
	while (tmp[0] != '-')//radi dok se ne dodlje do linije sa -----------------------------
	{
		Product product = processDataForFormat124(tmp);
		putNewProductInList(product);
		getline(inputf, tmp, END_OF_LINE);
	}
    
	std::string totalSumOfProducts, pdv, totalSumOfBill;//maskiraju podatke clanove klase Bill
	
	inputf.ignore(8);
	getline(inputf, totalSumOfProducts, END_OF_LINE);

	inputf.ignore(5);
	getline(inputf, pdv, END_OF_LINE);

	ignoreElementsUntil(inputf, END_OF_LINE);

	inputf.ignore(20);
	getline(inputf, totalSumOfBill, END_OF_LINE);

	this->totalSumOfProducts = std::stod(totalSumOfProducts, nullptr);
	this->pdv = std::stod(pdv, nullptr);
	this->totalSumOfBill = std::stod(totalSumOfBill, nullptr);
	inputf.close();
}

void Bill::processFormat5() 
{
	std::ifstream inputf(nameOfBill);
	std::string tmp;
    std::list <std::string> ProductsInString;
	
	int pos = nameOfBill.find("#", 0);
	nameOfClient = nameOfBill.substr(12, pos-12);
    
	auto dateString = nameOfBill.substr(pos+1, tmp.length()-pos);
	
	std::ofstream tmp_date("temp_date.txt");
	tmp_date << dateString;
	tmp_date.close();
	
	std::ifstream tmp_date2("temp_date.txt");
	processDate(tmp_date2);
	tmp_date2.close();

	_unlink("temp_date.txt");

    int ignoreHeader=0;
	while (!inputf.eof())
	{
		getline(inputf, tmp);
		if(ignoreHeader!=0 && tmp.size()!=0) ProductsInString.push_back(tmp);
		ignoreHeader++;
	}

	Product product;

	for (auto& k : ProductsInString)
	{
		int pos = k.find(",", 0);
		product.setCode(k.substr(0, pos));

		int pos2 = k.find(",", pos + 1);
		product.setQuantity(stod(k.substr(pos + 1, pos2 - pos), nullptr));

		int pos3 = k.find(",", pos2 + 1);
		product.setPricePerUnit(stod(k.substr(pos2 + 1, pos3 - pos2), nullptr));

		product.setTotal(stod(k.substr(pos3 + 1), nullptr));

		putNewProductInList(product);
	}

	inputf.close();
}

void Bill::processDate(std::ifstream &inputf)
{
	std::string day, month, year;
	for (int i = 0; i < 2; i++)
		day += inputf.get();
	inputf.get();
	for (int i = 0; i < 2; i++)
		month += inputf.get();
	inputf.get();
	for (int i = 0; i < 4; i++)
		year += inputf.get();
	inputf.get();
	date = Date::Date(std::stoi(day, nullptr, 10), std::stoi(month, nullptr, 10), std::stoi(year, nullptr, 10));
}

Product Bill::processDataForFormat124(std::string &tmp)
{
	std::string name;
	double quantity, pricePerUnit, total;
	double *productInfoPointers[3] = { &quantity, &pricePerUnit, &total };

	tmp += '-';//da bi bila jednolika obrada svih vrijednosti 
	int pos = tmp.find("-", 0);
	while (tmp[--pos] == ' ');//vracaj se unazad
	name = tmp.substr(0, pos + 1);

	int posOfFirstLine, posOfNextLine = tmp.find("-", 0);
	for (int i = 0; i < 3; i++)
	{
		posOfFirstLine = posOfNextLine;
		posOfNextLine = tmp.find("-", posOfNextLine+1);//uvecano za jedan jer find trazi i na poziciji posOfNextLine a tu sigurno nalazi znak -
		int posOfFirstDigit = posOfFirstLine, posOfLastDigit = posOfNextLine;
		while (tmp[++posOfFirstDigit] == ' ');
		while (tmp[--posOfLastDigit] == ' ');
		std::string value = tmp.substr(posOfFirstDigit, posOfLastDigit - posOfFirstDigit + 1);//podstring u kome se nalazi samo broj
		*productInfoPointers[i] = std::stod(value, nullptr);//std::stod - from string to doubles
	}
	return Product::Product(name, quantity, pricePerUnit, total);

}

Product Bill::processDataForFormat3(std::string &tmp)
{
	std::string name;
	double quantity, pricePerUnit, total;
	double *productInfoPointers[3] = { &quantity, &pricePerUnit, &total };

	tmp += '=';
	int pos = tmp.find("=",0);
	name = tmp.substr(0, pos);
	while (tmp[++pos] == '=');

	int posOfFirstCharOfEquality,posOfNextCharOfEquality = pos-1;

	for (int i = 0; i < 3; i++)
	{
		posOfFirstCharOfEquality = posOfNextCharOfEquality;
		posOfNextCharOfEquality = tmp.find("=", posOfNextCharOfEquality + 1);
		int posOfFirstDigit = posOfFirstCharOfEquality + 1,posOfLastDigit = posOfNextCharOfEquality-1;
		std::string  value = tmp.substr(posOfFirstDigit, posOfLastDigit - posOfFirstDigit + 1);
		*productInfoPointers[i] = std::stod(value, nullptr);

		while (tmp[++posOfNextCharOfEquality] == '=');
		posOfNextCharOfEquality -= 1;
	}
	return Product(name, quantity, pricePerUnit, total);
}

void Bill::putNewProductInList(const Product & product)
{
	
	for (auto& listProduct : list)
		if (listProduct.getCode() == product.getCode())
		{
			listProduct.setQuantity(product.getQuantity() + listProduct.getQuantity());
			listProduct.setTotal(product.getTotal() + listProduct.getTotal());
			return;
		}
		list.push_back(product);
		return;
}

void Bill::ignoreElementsUntil(std::ifstream &inputf, char boundary)
{
	while (inputf.get() != boundary);
}

int Bill::numberOfDigits(double data) 
{
	int numOfDigits = 0;
	while ( data >= 1)
		data/=10,numOfDigits++;
	return numOfDigits;
}


bool Bill::Validate()
{
	bool check1 = checkTotalOfEveryProduct();
	bool check2 = true, check3 = true;
	if (formatCode != 5)
	{
		check2 = checkTotalofAllproducts();
		check3 = checkTotalPlusPDV();
	}
	return check1 && check2 && check3;
}

bool Bill::checkTotalOfEveryProduct()//nije testirana
{
	bool check = true;
	for (auto& product : list)
		if ((product.getTotal() < product.getPricePerUnit() * product.getQuantity() - EPS) || ( product.getTotal() >product.getPricePerUnit() * product.getQuantity() + EPS))
		try
		{
			check = false;
			std::string errorMessage;
			errorMessage = "Za proizvod " + product.getCode() + " ukupna kolicina nije u okolini kolicina*cijena sa zadovoljavajucom tacnoscu";
			errorMessage += END_OF_LINE;
			errorMessage += "Ukupno : ";
			errorMessage += std::to_string(product.getTotal());
			errorMessage += END_OF_LINE;
			errorMessage += "Kolicina*Cijena : ";
			errorMessage += std::to_string(product.getPricePerUnit() * product.getQuantity());
			errorMessage += END_OF_LINE;
			errorMessage += "Tacnost : ";
			errorMessage += std::to_string(EPS);
			errorMessage += END_OF_LINE;
			throw ErrorException(nameOfBill, errorMessage);
		}
	    catch (ErrorException& ex)
		{
			ex.processException();
		}
	return check;
}

bool Bill::checkTotalofAllproducts()
{
	bool check = true;

	double total=0.0;
	for (auto& product : list)
		total += product.getTotal();

	if ((totalSumOfProducts < total- EPS) || (totalSumOfProducts > total + EPS))
	try
	{
		check = false;
		std::string errorMessage;
		errorMessage += "Za racun " + nameOfBill + " ukupna vrijednost na racunu bez pdv-a nije u okolini ukupne sume proizvoda sa zadovoljavajucom tacnoscu";
		errorMessage += END_OF_LINE;
		errorMessage += "Ukupno bez pdv-a : ";
		errorMessage += std::to_string(totalSumOfProducts);
		errorMessage += END_OF_LINE;
		errorMessage += "Ukupna suma proizvoda sa racuna : ";
		errorMessage += std::to_string(total);
		errorMessage += END_OF_LINE;
		errorMessage += "Tacnost : ";
		errorMessage += std::to_string(EPS);
		errorMessage += END_OF_LINE;
		throw ErrorException(nameOfBill, errorMessage);
	}
	catch (ErrorException& ex)
	{
		ex.processException();
	}
	return check;
}

bool Bill::checkTotalPlusPDV()
{
	bool check = true;

	if ((totalSumOfBill < totalSumOfProducts + pdv - EPS) || (totalSumOfBill > totalSumOfProducts + pdv + EPS) )
	try
	{
		check = false;
		std::string errorMessage;
		errorMessage += "Za racun " + nameOfBill + " ukupna vrijednost na racunu nije u okolini ukupne vrijednosti bez pdv-a + pdv sa zadovoljavajucom tacnoscu";
		errorMessage += END_OF_LINE;
		errorMessage += "Ukupna vrijednost : ";
		errorMessage += std::to_string(totalSumOfBill);
		errorMessage += END_OF_LINE;
		errorMessage += "Ukupna vrijednost bez pdv-a + pdv : ";
		errorMessage += std::to_string(totalSumOfProducts + pdv);
		errorMessage += END_OF_LINE;
		errorMessage += "Tacnost : ";
		errorMessage += std::to_string(EPS);
		errorMessage += END_OF_LINE;
		throw ErrorException(nameOfBill, errorMessage);
	}
	catch (ErrorException& ex)
	{
		ex.processException();
	}
	return check;
}



Bill::~Bill()
{}

Bill::Date::Date(const int day, const int month, const int year): day(day), month(month), year(year)
{}

bool isProcessedBill(const std::string file)
{
	std::ifstream inputFileLog(LOG);
	std::ifstream inputFileLogError(LOGERROR);
	if (inputFileLog.is_open())
	{
		std::string bill;
		while (!inputFileLog.eof())
		{
			getline(inputFileLog, bill);
			if (bill == file)
			{
				inputFileLog.close();
				return true;
			}
		}
		inputFileLog.close();
	}
	if (inputFileLogError.is_open())
	{
		std::string bill;
		while (!inputFileLogError.eof())
		{
			getline(inputFileLogError, bill);
			if (bill == file)
			{
				inputFileLogError.close();
				return true;
			}
		}
		inputFileLogError.close();
	}
	return false;
}

std::vector<std::string> returnVectorOfNotProcessedBills(const std::string directory)
{
	std::vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;
	std::ofstream logError(LOGERROR);
	std::string folder = FILE_OF_BILLS;
	folder += "\\";

	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData))
		{
			std::string file = fileData.cFileName;
			if (file.length() > 4 && (file.substr(file.length() - 4, 4) == ".txt" || file.substr(file.length() - 4, 4) == ".csv"))
			{
				if ((file.length() >= 10) && (file.substr(file.length() - 10, 6) == "_error"))
					logError << folder + file.substr(0, file.length() - 10) + file.substr(file.length() - 4, 4) << std::endl;
				else if (file != LOG && file != LOGERROR)
					files.push_back(folder + file);
			}
		}
	}
	logError.close();
	std::vector<std::string> filesToProcess;
	for (int i = 0; i < files.size(); i++)
	{
		if (isProcessedBill(files[i]) == false)
			filesToProcess.push_back(files[i]);
	}
	FindClose(hFind);
	if(files.size() > 0)
		files.erase(files.begin());
	return filesToProcess;
}

bool checkFormat1(const std::string file)
{
	std::ifstream inputFile(file);
	if (inputFile.is_open())
	{
		std::string tmp;
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Kupac:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Datum:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp.substr(0, 5) != "Racun")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Proizvod")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "kolicina")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "cijena")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "ukupno")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		std::string tmp1;
		do
		{
			tmp1 = "";
			getline(inputFile, tmp);
			for (int i = 0; i < tmp.length(); i++, tmp1 += "-");
		} while (!inputFile.eof() && tmp != tmp1);
		if (inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 7) != "Ukupno:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 4) != "PDV:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 19) != "Ukupno za placanje:")
		{
			inputFile.close();
			return false;
		}
		if (!inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		inputFile.close();
		return true;
	}
	return false;
}

bool checkFormat2(const std::string file)
{
	std::ifstream inputFile(file);
	if (inputFile.is_open())
	{
		std::string tmp;
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		if (tmp.substr(0, 11) != "Poslovnica:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp.substr(0, 12) != "Maloprodajni")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp.substr(0, 5) != "racun")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Kupac:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Proizvod")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "kolicina")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "cijena")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "-")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "ukupno")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		getline(inputFile, tmp);
		std::string tmp1;
		for (int i = 0; i < tmp.length(); i++, tmp1 += "-");
		if (tmp != tmp1)
		{
			inputFile.close();
			return false;
		}
		do
		{
			tmp1 = "";
			getline(inputFile, tmp);
			for (int i = 0; i < tmp.length(); i++, tmp1 += "-");
		} while (!inputFile.eof() && tmp != tmp1);
		if (inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		if (tmp.substr(0, 7) != "Ukupno:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 4) != "PDV:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 19) != "Ukupno za placanje:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Datum:")
		{
			inputFile.close();
			return false;
		}
		if (!inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		inputFile.close();
		return true;
	}
	return false;
}

bool checkFormat3(const std::string file)
{
	std::ifstream inputFile(file);
	if (inputFile.is_open())
	{
		std::string tmp;
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		if (tmp.substr(0, 11) != "Poslovnica:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Kupac:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (tmp.substr(0, 6) != "Datum:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp.substr(0, 12) != "Maloprodajni")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp.substr(0, 5) != "racun")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Proizvod")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "Kolicina")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "Cijena")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "Ukupno")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		std::string tmp1;
		for (int i = 0; i < tmp.length(); i++, tmp1 += "-");
		if (tmp != tmp1)
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		do
		{
			tmp1 = "";
			getline(inputFile, tmp);
			for (int i = 0; i < tmp.length(); i++, tmp1 += "-");
		} while (!inputFile.eof() && tmp != tmp1);
		if (inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Ukupno:")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		inputFile >> tmp;
		if (tmp != "PDV:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		getline(inputFile, tmp);
		inputFile >> tmp;
		if (tmp != "Ukupno")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "za")
		{
			inputFile.close();
			return false;
		}
		inputFile >> tmp;
		if (tmp != "placanje:")
		{
			inputFile.close();
			return false;
		}
		getline(inputFile, tmp);
		if (!inputFile.eof())
		{
			inputFile.close();
			return false;
		}
		inputFile.close();
		return true;
	}
	return false;
}

bool checkFormat5(const std::string bill)
{
	std::ifstream file(bill);
	int count = 0;
	std::string fileFormatString1 = "Sifra,Kolicina,Cijena,Ukupno";
	std::string tmp;
	std::getline(file, tmp);
	if (tmp != fileFormatString1)
	{
		file.close();
		return false;
	}
	do
	{
		std::getline(file, tmp);
		for (int i = 0; i < tmp.length() - 1; i++)
			if (tmp[i] == ',')
				count++;
		if (count != 3)
		{
			file.close();
			return false;
		}
		count = 0;
	} while (file.peek() != std::ifstream::traits_type::eof());
	file.close();
	return true;
}

bool checkFormat4(const std::string bill)
{
	std::ifstream file(bill);
	std::string fileFormatString4 = "";
	std::string fileFormatString5 = "";
	int count = 0;
	if (file.is_open())
	{
		std::string tmp;
		std::getline(file, tmp);
		if (tmp.substr(0, 7) != "Kupac: ")
		{
			file.close();
			return false;
		}
		std::getline(file, tmp);
		if (tmp.substr(0, 7) != "Datum: ")
		{
			file.close();
			return false;
		}
		std::getline(file, tmp);
		std::getline(file, tmp);
		std::getline(file, tmp);
		std::getline(file, tmp);
		if (tmp.substr(0, 8) != "Proizvod")
		{
			file.close();
			return false;
		}
		int pos1 = tmp.find_first_not_of(' ', 9);
		if (tmp[pos1] != '-')
		{
			file.close();
			return false;
		}
		int pos2 = tmp.find_first_not_of(' ', pos1 + 1);
		if (tmp.substr(pos2, 8) != "kolicina")
		{
			file.close();
			return false;
		}
		pos2 += 8;
		pos1 = tmp.find_first_not_of(' ', pos2 + 1);
		if (tmp[pos1] != '-')
		{
			file.close();
			return false;
		}
		pos2 = tmp.find_first_not_of(' ', pos1 + 1);
		if (tmp.substr(pos2, 6) != "cijena")
		{
			file.close();
			return false;
		}
		pos2 += 6;
		pos1 = tmp.find_first_not_of(' ', pos2 + 1);
		if (tmp[pos1] != '-')
		{
			file.close();
			return false;
		}
		pos2 = tmp.find_first_not_of(' ', pos1 + 1);
		if (tmp.substr(pos2, 6) != "ukupno")
		{
			file.close();
			return false;
		}
		std::getline(file, fileFormatString4);
		if (fileFormatString4.empty())
		{
			file.close();
			return false;
		}
		while (count != fileFormatString4.length() - 1)
		{
			if (fileFormatString4[count++] != '-')
			{
				file.close();
				return false;
			}
		}
		count = 0;
		std::getline(file, fileFormatString5);
		while (fileFormatString5 != fileFormatString4)
			std::getline(file, fileFormatString5);
		if (file.peek() == std::ifstream::traits_type::eof())
		{
			file.close();
			return false;
		}
		std::getline(file, tmp);
		if (tmp.substr(0, 8) != "Ukupno: ")
		{
			file.close();
			return false;
		}
		std::getline(file, tmp);
		if (tmp.substr(0, 5) != "PDV: ")
		{
			file.close();
			return false;
		}
		count = 0;
		std::getline(file, fileFormatString4);
		if (fileFormatString4.empty())
		{
			file.close();
			return false;
		}
		while (count != fileFormatString4.length() - 1)
		{
			if (fileFormatString4[count++] != '=')
			{
				file.close();
				return false;
			}
		}
		std::getline(file, tmp);
		if (tmp.substr(0, 20) != "Ukupno za placanje: ")
		{
			file.close();
			return false;
		}
		tmp.clear();
		std::getline(file, tmp);
		if (!tmp.empty())
		{
			file.close();
			return false;
		}
		std::getline(file, tmp);
		if (tmp != fileFormatString4)
		{
			file.close();
			return false;
		}
		file.close();
		return true;
	}
	return false;
};

void Bill::exportForCustomer()
{
	std::ofstream output;
	std::string directory = "Kupac\\";
	directory += this->nameOfClient;
	directory += ".txt";
	CreateDirectory("Kupac", NULL);
	output.open(directory, std::ios::in);
	if (!output.is_open())
	{
		output.open(directory);
		output << std::setw(20) << std::left << "Datum:";
		output << std::setw(20) << std::left << "Sifra:";
		output << std::setw(20) << std::left << "Kolicina:";
		output << std::setw(20) << std::left << "Cijena:";
		output << std::setw(20) << std::left << "Ukupno:" << std::endl;
		std::string tmp;
		while (tmp.length() != 87)
			tmp += "-";
		output << tmp << std::endl;
		for (auto& product : this->list)
		{
			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getCode();
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		output.close();
	}
	else
	{
		output.close();
		output.open(directory, std::ios::app);
		for (auto product : this->list)
		{

			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getCode();
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		output.close();
	}
}

void Bill::exportForProduct()
{
	std::ofstream output;
	CreateDirectory("Proizvod", NULL);
	for (auto& product : this->list)
	{
		std::string directory = "Proizvod\\";
		directory += product.getCode();
		directory += ".txt";
		output.open(directory, std::ios::in);
		if (!output.is_open())
		{
			output.open(directory);
			output << std::setw(20) << std::left << "Kupac:";
			output << std::setw(20) << std::left << "Datum:";
			output << std::setw(20) << std::left << "Kolicina:";
			output << std::setw(20) << std::left << "Cijena:";
			output << std::setw(20) << std::left << "Ukupno:" << std::endl;
			std::string tmp;
			while (tmp.length() != 87)
				tmp += "-";
			output << tmp << std::endl;
			output << std::setw(20) << std::left << this->nameOfClient;
			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
			output.close();
		}
		else
		{
			output.close();
			output.open(directory, std::ios::app);
			output << std::setw(20) << std::left << this->nameOfClient;
			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
			output.close();
		}
	}
}

void Bill::exportForMonth()
{
	std::ofstream output;
	std::string directory = "Mjesec\\";
	directory += month[this->date.month - 1];
	directory += " ";
	directory += std::to_string(this->date.year);
	directory += ".txt";
	CreateDirectory("Mjesec", NULL);
	output.open(directory, std::ios::in);
	if (!output.is_open())
	{
		output.open(directory);
		output << std::setw(20) << std::left << "Kupac:";
		output << std::setw(20) << std::left << "Datum:";
		output << std::setw(20) << std::left << "Sifra:";
		output << std::setw(20) << std::left << "Kolicina:";
		output << std::setw(20) << std::left << "Cijena:";
		output << std::setw(20) << std::left << "Ukupno:" << std::endl;
		std::string tmp;
		while (tmp.length() != 107)
			tmp += "-";
		output << tmp << std::endl;
		for (auto& product : this->list)
		{
			output << std::setw(20) << std::left << this->nameOfClient;
			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getCode();
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		output.close();
	}
	else
	{
		output.close();
		output.open(directory, std::ios::app);
		for (auto product : this->list)
		{
			output << std::setw(20) << std::left << this->nameOfClient;
			output << std::setw(20) << std::left << std::to_string(this->date.day) + "/" + std::to_string(this->date.month) + "/" + std::to_string(this->date.year);
			output << std::setw(20) << std::left << product.getCode();
			output << std::setw(20) << std::left << product.getQuantity();
			output << std::setw(20) << std::left << product.getPricePerUnit();
			output << std::setw(20) << std::left << product.getTotal() << std::endl;
		}
		output.close();
	}
}

