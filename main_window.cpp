#include "main_window.h"
#include <fstream>
#include <cmath>

using namespace std;

MainWindow::MainWindow(MyDataStore* ds)

{
	this->ds = ds;
	initializeComponents();
	setUpLayout();
	connectEvents();
	int x = width()*2.5;
	int y = height()*2.5;
	amazonWindow->setFixedSize(x,y);
	int w = width()*1.4;
	int l = height()*0.7;
	loginWindow->setFixedSize(w,l);
	createUserComboBox();
	viewCartButton->setEnabled(false);
	searchProductInput->setEnabled(false);
	searchButton->setEnabled(false);
	sortButton->setEnabled(false);
	addToCartButton->setEnabled(false);
	viewReviewsButton->setEnabled(false);
	addReviewButton->setEnabled(false);

	// Set overall layout
	setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
	delete quitAmazonButton;
	delete filenameInput;
	delete buyCartButton;
	delete removeItemButton;
	delete productCartListWidget;
	delete buyCartLayout;
	delete userCartLayout;
	delete userCartWidget;
	delete addReviewYearComboBox;
	delete addReviewMonthComboBox;
	delete addReviewDateComboBox;
	delete addReviewDateLayout;
	delete addReviewRateInput;
	delete addReviewRateLabel;
	delete addReviewRateLayout;
	delete addReviewTextLayout;
	delete addReviewQPushButton;
	delete addReviewTextInput;
	delete addReviewTextLabel;
	delete addReviewLayout;
	delete addReviewWindow;
	delete reviewListWidget;
	delete reviewListDisplayLayout;
	delete sortButton;
	delete rankingSort;
	delete alphaNumSort;
	delete productListWidget;
	delete productListDisplayLayout;
	delete addReviewButton;
	delete viewReviewsButton;
	delete addToCartButton;
	delete productQtyLabel;
	delete productNameLabel;
	delete productDisplayLayout;
	delete searchProductInput;
	delete andButton;
	delete orButton;
	delete searchButtonLayout;
	delete searchDisplayLayout;
	delete userComboBox;
	delete comboSelectButton;
	delete yesUserLabel;
	delete yesUserBalanceLabel;
	delete yesUserNameLabel;
	delete viewCartButton;
	delete userDisplayLayout;
	delete overallLayout;
}

void MainWindow::initializeComponents() {
	setWindowTitle("Amazon"); 	// Title
	mainLayout = new QHBoxLayout();
	loginWindow = new QWidget();
	amazonWindow = new QWidget();

	overallLayout = new QGridLayout(); 	// Overall layout	
	//Log in
	loginLayout = new QVBoxLayout();
	loginButtonLayout = new QHBoxLayout();
	quitLoginButton = new QPushButton("Quit");
	loginButton = new QPushButton("Login");
	newUserButton = new QPushButton("Create Account");
	userPasswordInput = new QLineEdit();
	userPasswordInput->setPlaceholderText("Password");
	userNameInput = new QLineEdit();
	userNameInput->setPlaceholderText("Username");
	quitLoginLayout = new QHBoxLayout();
	mainLabel = new QLabel("Log in or create your amazon account");
	
	// User
	userDisplayLayout = new QHBoxLayout();
	users_ = ds->getUserVector(); //user vector
	userComboBox = new QComboBox();

	//used to be createComboBox
	comboSelectButton = new QPushButton("select user"); 
	yesUserLabel = new QLabel("Current User:");
	yesUserNameLabel = new QLabel();
	yesUserBalanceLabel = new QLabel();

	// view user Cart
	viewCartLayout = new QHBoxLayout();
	viewCartButton = new QPushButton("View Cart");
	signOutButton = new QPushButton("Sign Out");

	// Search and Rating
	searchDisplayLayout = new QVBoxLayout();
	searchProductInput = new QLineEdit();
	searchProductInput->setPlaceholderText("Search for a product");
	searchButtonLayout = new QHBoxLayout();
	searchButton = new QPushButton("Search");
	andButton = new QRadioButton("AND");
	orButton = new QRadioButton("OR");

	//Product List Layout
	productListDisplayLayout = new QHBoxLayout();
	productListWidget = new QListWidget();

	sortDisplayLayout = new QHBoxLayout();
	alphaNumSort = new QRadioButton("Alphanumerical");
	rankingSort = new QRadioButton("Ranking");
	sortButton = new QPushButton("Sort");
	

	//Product Description and Rating
	productDisplayLayout = new QVBoxLayout();
	productNameLabel = new QLabel(); //display selected product name
	productQtyLabel = new QLabel();
	addToCartButton = new QPushButton("Add to my Cart");
	viewRecommendations = new QPushButton("View Recommendations");
	reviewDisplayLayout = new QHBoxLayout();
	viewReviewsButton = new QPushButton("View Reviews");
	addReviewButton = new QPushButton("Add Review");

	//Product Recommendations
	productRecommendationsWidget = new QWidget();
	productRecommendationsLayout = new QVBoxLayout();
	productRecommendationsList = new QListWidget();
	doneButton = new QPushButton("Done");


	//Review List Layout
	reviewListDisplayLayout = new QVBoxLayout();
	reviewListWidget = new QListWidget();

	//add review window
	addReviewWindow = new QWidget();
	addReviewLayout = new QHBoxLayout();
	addReviewRateLayout = new QHBoxLayout();
	addReviewRateLabel = new QLabel("Input Rating");
	addReviewRateInput = new QLineEdit();
	addReviewDateLayout = new QHBoxLayout();
	addReviewDateComboBox = new QComboBox();
	addReviewMonthComboBox = new QComboBox();
	addReviewYearComboBox = new QComboBox();
	addReviewTextLayout = new QHBoxLayout();
	addReviewTextLabel = new QLabel("Input Text");
	addReviewTextInput = new QLineEdit();
	addReviewWindow->hide();
	addReviewQPushButton = new QPushButton("ADD");

	//view cart
	userCartWidget = new QWidget();
	userCartLayout = new QVBoxLayout();
	productCartListWidget = new QListWidget();

	//buy cart
	buyCartLayout = new QHBoxLayout();
	removeItemButton = new QPushButton("Remove Item");
	buyCartButton = new QPushButton("Buy Cart");

	//save database layout
	saveDatabaseLayout = new QHBoxLayout();
	filenameInput = new QLineEdit();
	saveDatabaseButton = new QPushButton("Save");
	quitAmazonButton = new QPushButton("Quit");
}

void MainWindow::setUpLayout() {
	
	mainLayout->addWidget(loginWindow);
	loginWindow->setLayout(loginLayout);
	loginLayout->addWidget(mainLabel);
	//overallLayout->addLayout(loginLayout, 0, 0);
	loginLayout->addWidget(userNameInput);
	loginLayout->addWidget(userPasswordInput);
	loginLayout->addLayout(loginButtonLayout);
	loginButtonLayout->addWidget(loginButton);
	loginButtonLayout->addWidget(newUserButton);
	loginLayout->addLayout(quitLoginLayout);
	quitLoginLayout->addWidget(quitLoginButton);

	mainLayout->addWidget(amazonWindow);
	amazonWindow->setLayout(overallLayout);

	amazonWindow->hide();

	//User
	overallLayout->addLayout(userDisplayLayout, 1, 0);
	userDisplayLayout->addWidget(yesUserLabel);
	userDisplayLayout->addWidget(yesUserNameLabel);
	userDisplayLayout->addWidget(yesUserBalanceLabel);
	userDisplayLayout->addLayout(viewCartLayout);
	viewCartLayout->addWidget(viewCartButton);
	viewCartLayout->addWidget(signOutButton);


	//Search Display Layout
	overallLayout->addLayout(searchDisplayLayout, 2, 0);
	searchDisplayLayout->addWidget(searchProductInput);
	searchDisplayLayout->addLayout(searchButtonLayout);
	searchButtonLayout->addWidget(andButton);
	searchButtonLayout->addWidget(orButton);
	searchDisplayLayout->addWidget(searchButton);
	overallLayout->addLayout(productListDisplayLayout, 3, 0);
	productListDisplayLayout->addWidget(productListWidget);
	productListDisplayLayout->addWidget(reviewListWidget);

	searchDisplayLayout->addLayout(sortDisplayLayout);
	sortDisplayLayout->addWidget(alphaNumSort);
	sortDisplayLayout->addWidget(rankingSort);
	searchDisplayLayout->addWidget(sortButton);

	//product Display Layout
	overallLayout->addLayout(productDisplayLayout, 4, 0);
	productDisplayLayout->addWidget(productNameLabel);
	productDisplayLayout->addWidget(productQtyLabel);
	productDisplayLayout->addWidget(addToCartButton);
	productDisplayLayout->addWidget(viewRecommendations);

	//Product Recommendations
	mainLayout->addWidget(productRecommendationsWidget);
	productRecommendationsWidget->setLayout(productRecommendationsLayout);
	productRecommendationsLayout->addWidget(productRecommendationsList);
	productRecommendationsLayout->addWidget(doneButton);
	productRecommendationsWidget->hide();
	

	//review list layout
	overallLayout->addLayout(reviewListDisplayLayout, 5,0);
	overallLayout->addLayout(reviewDisplayLayout, 6, 0);
	reviewDisplayLayout->addWidget(viewReviewsButton);
	reviewDisplayLayout->addWidget(addReviewButton);

	// add review window
	addReviewLayout->addLayout(addReviewRateLayout);
	addReviewRateLayout->addWidget(addReviewRateLabel);
	addReviewRateLayout->addWidget(addReviewRateInput);
	addReviewLayout->addLayout(addReviewDateLayout);
	addReviewDateLayout->addWidget(addReviewDateComboBox);
	addReviewDateLayout->addWidget(addReviewMonthComboBox);
	addReviewDateLayout->addWidget(addReviewYearComboBox);
	addReviewLayout->addLayout(addReviewTextLayout);
	addReviewTextLayout->addWidget(addReviewTextLabel);
	addReviewTextLayout->addWidget(addReviewTextInput);
	addReviewTextLayout->addWidget(addReviewQPushButton);
	addReviewWindow->setLayout(addReviewLayout);

	//view cart window
	userCartLayout->addWidget(productCartListWidget);
	userCartWidget->setLayout(userCartLayout);

	//buy cart
	userCartLayout->addLayout(buyCartLayout);
	buyCartLayout->addWidget(buyCartButton);
	buyCartLayout->addWidget(removeItemButton);

	//save database
	overallLayout->addLayout(saveDatabaseLayout, 7, 0);
	saveDatabaseLayout->addWidget(filenameInput);
	saveDatabaseLayout->addWidget(saveDatabaseButton);
	saveDatabaseLayout->addWidget(quitAmazonButton);
}

void MainWindow::connectEvents() {
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewUserCart()));
	connect(loginButton, SIGNAL(clicked()), this, SLOT(loginUser()));
	connect(newUserButton, SIGNAL(clicked()), this, SLOT(createUser()));
	connect(quitLoginButton, SIGNAL(clicked()), this, SLOT(quitAmazon()));
	connect(productListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(enableReview()));
	connect(searchButton, SIGNAL(clicked()), this, SLOT(connectSearch()));
	connect(sortButton, SIGNAL(clicked()), this, SLOT(sort()));
	connect(productListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(getCurrentSelectedProduct(int)));
	connect(addToCartButton, SIGNAL(clicked()), this, SLOT(addProductToCart()));
	connect(viewRecommendations, SIGNAL(clicked()), this, SLOT(getRecommendations()));
	connect(doneButton, SIGNAL(clicked()), this, SLOT(doneRecommendations()));
	connect(signOutButton, SIGNAL(clicked()), this, SLOT(signOut()));
	connect(viewReviewsButton, SIGNAL(clicked()), this, SLOT(viewProductReviews()));
	connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addProductReview()));
	connect(addReviewQPushButton, SIGNAL(clicked()), this, SLOT(hideAddReviewWindow()));
	connect(viewCartButton, SIGNAL(clicked()), this, SLOT(viewUserCart()));
	connect(buyCartButton, SIGNAL(clicked()), this, SLOT(buyUserCart()));
	connect(removeItemButton, SIGNAL(clicked()), this, SLOT(removeItem()));
	connect(saveDatabaseButton, SIGNAL(clicked()), this, SLOT(saveDatabase()));
	connect(quitAmazonButton, SIGNAL(clicked()), this, SLOT(quitAmazon()));
}


void MainWindow::doneRecommendations() {
	productRecommendationsWidget->hide();
	amazonWindow->show();
}

void MainWindow::getRecommendations() {
	productRecommendationsWidget->show();
	amazonWindow->hide();
	vector<std::pair<string, double> > input = ds->makeSuggestion(username);
	if (input.size() == 0) {
		cout << "it;s empty" << endl;
		return;
	}
	string file = "rec.txt";
	ofstream ofile(file.c_str());
	ofile << username << endl;
 	mergeSort(input, doubleRating());
	 double d;
	 vector<std::pair<string, double> >::iterator vit;
	 for (vit = input.begin(); vit != input.end(); vit++) {
		Product * p = ds->findProduct(vit->first);
		string prodS = p->displayString();
		stringstream ss;
		ss.clear();
		d = vit->second;
		ss << d;
		string myDouble = "";
		ss >> myDouble;
		 QString myQstr = QString::fromStdString("Name: " + prodS + "  Score: " + myDouble + "\n");
		 ofile << "Name: " << prodS << "  Score: " << myDouble << "\n";
		 productRecommendationsList->addItem(myQstr);
	 }
	 ofile.close();
}

void MainWindow::loginUser() {
	
	std::string username = userNameInput->text().toStdString();
	std::string password = userPasswordInput->text().toStdString();

	unsigned int hash = hashFunction(password);
	cout << "hash" << hash << endl;
	User *myUser = NULL;
	unsigned int userHash;
	for (unsigned int i = 0; i < users_.size(); i++) {
		if (username == users_[i]->getName()) {
			myUser = users_.at(i);
		} 
		cout << "test " << endl;
	}
	if (myUser == NULL) {
			QMessageBox mybox(this);  // this is the pointer to the current widget
      		mybox.setText("User does not exist");
      		mybox.exec();
			  return;
		}
		userHash = myUser->getHash();
		cout << "userHash" << userHash << endl;

		if (hash == userHash) {
			ds->userLoggedIn = myUser;
			cout << "equalled" << endl;
			loginWindow->hide();
			amazonWindow->show();
			displayUserComboBox();
		}

	if (hash != userHash) {
		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("Incorrect Password");
      	mymsg.exec();
	}
	
	userNameInput->clear();
	userPasswordInput->clear();
}

void MainWindow::createUser() {
	cout << "in create user" << endl;
	std::string userCreatename = userNameInput->text().toStdString();
	std::string createPassword = userPasswordInput->text().toStdString();
	cout << "username" << userCreatename << endl;
	cout << "password" << createPassword << endl;
	unsigned int newUserHash = hashFunction(createPassword);
	cout << "hash" << newUserHash << endl;
	User* newUser = new User(userCreatename, 100, 0, newUserHash);
	users_.push_back(newUser);
	ds->addUser(newUser);
	ds->userLoggedIn = newUser;
	userNameInput->clear();
	userPasswordInput->clear();
	//displayUserComboBox();
}

unsigned int MainWindow::hashFunction(string password) {
	unsigned long long p = 0;

    unsigned long long numChars = password.length();
    for (unsigned int i = 0; i < numChars; i++) {
        unsigned long long myChar = (unsigned long long)password[i];
        p += myChar * (unsigned long long)pow(128, numChars - i- 1);
    }

    unsigned int w4 = p%65521;
    unsigned int w3 = (p/65521)%65521;
    unsigned int w2 = ((p/65521)/65521)%65521;
    unsigned int w1 = (((p/65521)/65521)/65521)%65521;
    unsigned int result = (45912 * w1 + 35511 * w2 + 65169 * w3 + 4625 * w4) % 65521;

	return result;
}

void MainWindow::signOut() {
	amazonWindow->hide();
	loginWindow->show();
}


void MainWindow::enableSearch() {
	viewCartButton->setEnabled(true);
	searchProductInput->setEnabled(true);
	searchButton->setEnabled(true);
	sortButton->setEnabled(true);
}

void MainWindow::enableReview() {
	addToCartButton->setEnabled(true);
	viewReviewsButton->setEnabled(true);
	addReviewButton->setEnabled(true);
}

void MainWindow::displayUserComboBox() {
	username = ds->userLoggedIn->getName();
	cout << "username" << username << endl;
	for (unsigned int i = 0; i < users_.size(); i++) {
		if (username == users_[i]->getName()) {
			qstrName = QString::fromStdString(users_[i]->getName());
			qstrBalance = QString::number(users_[i]->getBalance());
			yesUserNameLabel->setText(qstrName);
			yesUserBalanceLabel->setText(qstrBalance);
		}
	}
	enableSearch();
}


void MainWindow::createUserComboBox() {
	for (unsigned int i = 0; i < users_.size(); i++) {
		qstrName = QString::fromStdString(users_[i]->getName());
		userComboBox->addItem(qstrName);	
	}
}

void MainWindow::connectSearch() {
	productListWidget->clear();

	QString qstrWords = searchProductInput->text();
	string searchWords = qstrWords.toStdString();
	std::set<string> wordsSet = parseStringToWords(searchWords);
	std::set<string>::iterator it;
	std::vector<string> terms;

	for (it = wordsSet.begin(); it != wordsSet.end(); it++) {
		terms.push_back(*it);
	}
	if (andButton->isChecked()) {
		items = ds->search(terms, 0);
	} else if (orButton->isChecked()) {
		items = ds->search(terms, 1);
	}
	std::vector<Product*>::iterator vit;
	for (vit = items.begin(); vit != items.end(); vit++) {
		QString myQstr = QString::fromStdString((*vit)->displayString());
		productListWidget->addItem(myQstr);
	}
}

void MainWindow::sort() {
	
	if (alphaNumSort->isChecked()) {
		mergeSort(items, productName());
	} else if (rankingSort->isChecked()) {
		mergeSort(items, averageRating());
	}
	productListWidget->clear();
	std::vector<Product*>::iterator vit;
	for (vit = items.begin(); vit != items.end(); vit++) {
		QString myQstr = QString::fromStdString((*vit)->displayString());
		productListWidget->addItem(myQstr);
	}
}

void MainWindow::getCurrentSelectedProduct(int i) {
	if (i >= (int)items.size()) return;
	currentSelectedProduct = items[i];
	qstrName = QString::fromStdString(currentSelectedProduct->getName());
	qstrBalance = QString::number(currentSelectedProduct->getQty());
	productNameLabel->setText(qstrName);
	productQtyLabel->setText(qstrBalance);
}

void MainWindow::addProductToCart() {
	int i = 0;
	std::vector<Product*>::iterator vit;
	for (vit = items.begin(); vit != items.end(); vit++) {
		i++;
		if ((*vit)->getName() == currentSelectedProduct->getName()) {
			break;
		}
		
	}
	cout << currentSelectedProduct->getName() << endl;
	cout << "i" << i << endl;
	ds->addToCart(username, i);

}

void MainWindow::viewProductReviews() {
	reviewListWidget->clear();

	std::vector<Review*>::iterator vit;
	cout << currentSelectedProduct->getName() << endl;
	

	std::vector<Review*> reviews = currentSelectedProduct->getReviews();
	
	mergeSort(reviews, reviewDate());
	for (vit = reviews.begin(); vit != reviews.end(); vit++) {
		QString myQstr = QString::fromStdString((*vit)->displayString());
		reviewListWidget->addItem(myQstr);
	}


}

void MainWindow::hideAddReviewWindow() {

	stringstream ss;
	string n = currentSelectedProduct->getName();

	// set rating
	string rateString = addReviewRateInput->text().toStdString();
	QString newReviewDate = addReviewDateComboBox->currentText();
	QString newReviewMonth = addReviewMonthComboBox->currentText();
	QString newReviewYear = addReviewYearComboBox->currentText();
	QString newReviewText = addReviewTextInput->text();

	ss.clear();
	ss.str(rateString);
	int rate = -1;
	ss >> rate;
	string date = newReviewYear.toStdString() + "-" + newReviewMonth.toStdString() + "-" + newReviewDate.toStdString();
	string textReview = newReviewText.toStdString();

	Review* newReview = new Review(n, rate, username, date, textReview);
	ds->addReview(newReview);
	addReviewWindow->hide();
	viewProductReviews();
}

void MainWindow::addProductReview() {
	addReviewWindow->show();
	
	stringstream ss;

	// populate data combo box
	for (unsigned int i = 1; i < 32; i++) {
		ss.clear();
		ss << i;
		string myI = "";
		ss >> myI;
		qstrName = QString::fromStdString(myI);
		addReviewDateComboBox->addItem(qstrName);	
	}

	//populate month combo box
	for (unsigned int i = 1; i < 13; i++) {
		ss.clear();
		ss << i;
		string myI = "";
		ss >> myI;
		qstrName = QString::fromStdString(myI);
		addReviewMonthComboBox->addItem(qstrName);	
	}

	//populate year combo box
	for (unsigned int i = 2016; i < 2031; i++) {
		ss.clear();
		ss << i;
		string myI = "";
		ss >> myI;
		qstrName = QString::fromStdString(myI);
		addReviewYearComboBox->addItem(qstrName);	
	}

}

void MainWindow::viewUserCart() {
	userCartWidget->show();
	productCartListWidget->clear();
	userCarts = ds->getUserCartsMap();
	userMap = ds->getUserMap();
	u = userMap[username];
	cart = userCarts[u];
	std::list<Product* >::iterator it = cart.begin();
	cout << u->getName() << endl;
	if (cart.empty()) {
		return;
	}
	ds->viewCart(username);
	for (; it != cart.end(); it++) {
	QString myQstr = QString::fromStdString((*it)->displayString());
	productCartListWidget->addItem(myQstr);
	}
	
}

void MainWindow::buyUserCart() {
	ds->buyCart(username);
	//productCartListWidget->clear();
	for (unsigned int i = 0; i < users_.size(); i++) {
		if (username == users_[i]->getName()) {
			qstrBalance = QString::number(users_[i]->getBalance());
			yesUserBalanceLabel->setText(qstrBalance);
		}
	}
}

void MainWindow::removeItem() {

	if (productCartListWidget->count() == 0) {
		return;
	}
	QString myProduct = productCartListWidget->currentItem()->text();
	string myProductString = myProduct.toStdString();
	cout << myProductString << endl;
	std::list<Product* >::iterator it;
	Product* p;

	for (it = cart.begin(); it != cart.end(); it++) {
		if (myProductString == (*it)->displayString()) {
			p = *it;
		}	
	}
	ds->removeFromCart(username, p);

	viewUserCart();
	
}

void MainWindow::saveDatabase() {
	if (filenameInput->text().isEmpty()) {
		return;
	}
	string filename = filenameInput->text().toStdString();
	std::ofstream ofile(filename.c_str());
	ds->dump(ofile);
	ofile.close();
}

void MainWindow::quitAmazon() {
	close();
}


