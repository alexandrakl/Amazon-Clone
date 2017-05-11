#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include "mydatastore.h"
#include "user.h"
#include "msort.h"
#include "product.h"
#include <string>
#include <vector>
#include <QComboBox>
#include <QRadioButton>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <QMessageBox>
#include <string>
#include "heap.h"



class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(MyDataStore* ds);
	~MainWindow();

private slots:
	void initializeComponents();
	void setUpLayout();
	void connectEvents();
	void loginUser();
	void createUser();
	unsigned int hashFunction(std::string password);
	void signOut();
	void enableSearch();
	void enableReview();
	void createUserComboBox();
	void displayUserComboBox();
	void connectSearch();
	void sort();
	void getCurrentSelectedProduct(int i);
	void addProductToCart();
	void getRecommendations();
	void doneRecommendations();
	void viewProductReviews();
	void addProductReview();
	void hideAddReviewWindow();
	void viewUserCart();
	void buyUserCart();
	void removeItem();
	void saveDatabase();
	void quitAmazon();


private:
	// UI
	QHBoxLayout* mainLayout;
	QWidget* loginWindow;
	QWidget* amazonWindow;
	QGridLayout* overallLayout; // Overall Horizontal Layout
	MyDataStore* ds;
	Heap<int> myHeap;
	
	//Log in
	QVBoxLayout* loginLayout;
	QPushButton* loginButton;
	QLineEdit* userPasswordInput;
	QLineEdit* userNameInput; //box input user
	QHBoxLayout* loginButtonLayout;
	QPushButton* quitLoginButton;
	QPushButton* newUserButton;
	QHBoxLayout* quitLoginLayout;
	QLabel* mainLabel;

	// Display current user
	QHBoxLayout* userDisplayLayout; //user vertical layout	
	std::vector<User*> users_; //vector of users
	QPushButton* selectButton; //select user button
	QComboBox* userComboBox; //user combo box
	QPushButton* comboSelectButton; //user combo select button

	// user exists
	std::string username; //yes string c++
	QLabel* yesUserLabel; // yes user label
	QLabel* yesUserNameLabel; //yes user name label
	QLabel* yesUserBalanceLabel; //yes user balance label
	QString qstrBalance; // yes user qstring balance
	QString qstrName; // yes user qstring name

	// user does not exist
	QVBoxLayout* noUserLayout; //Nouser layout popout
	QWidget* noUserWidget; //no user widget
	QLabel* noUserLabel; //no user label

	//view cart
	QHBoxLayout* viewCartLayout;
	QPushButton* viewCartButton;
	QPushButton* signOutButton;

	//Display search
	QVBoxLayout* searchDisplayLayout;
	QLineEdit* searchProductInput;
	QHBoxLayout* searchButtonLayout;
	QPushButton* searchButton;
	QRadioButton* andButton;
	QRadioButton* orButton;
	
	//Product List Display Layout
	QHBoxLayout* productListDisplayLayout;
	QListWidget* productListWidget;
	std::vector<Product*> items;

	// sort layout
	QHBoxLayout* sortDisplayLayout;
	QRadioButton* alphaNumSort;
	QRadioButton* rankingSort;
	QPushButton* sortButton;

	//Product Display Layout
	QVBoxLayout* productDisplayLayout;
	QHBoxLayout* reviewDisplayLayout;
	QPushButton* addToCartButton;
	QPushButton* viewReviewsButton;
	QPushButton* addReviewButton;
	QPushButton* viewRecommendations;

	//ProductRecommendations
	QWidget* productRecommendationsWidget;
	QVBoxLayout* productRecommendationsLayout;
	QListWidget* productRecommendationsList;
	QPushButton* doneButton;

	//Review List Layout
	QVBoxLayout* reviewListDisplayLayout;
	QListWidget* reviewListWidget;

	//for selecting
	Product* currentSelectedProduct;
	QString currentSelectedProductName;
	QLabel* productNameLabel; // product name label
	QLabel* productQtyLabel; //product qty label
	int currentSelectedIndex;

	//AddReview Layout
	QWidget* addReviewWindow;
	QHBoxLayout* addReviewLayout;
	QHBoxLayout* addReviewRateLayout;
	QLabel* addReviewRateLabel;
	QLineEdit* addReviewRateInput;
	QHBoxLayout* addReviewDateLayout;
	QComboBox* addReviewDateComboBox;
	QComboBox* addReviewMonthComboBox;
	QComboBox* addReviewYearComboBox;
	QHBoxLayout* addReviewTextLayout;
	QLabel* addReviewTextLabel;
	QLineEdit* addReviewTextInput;
	QPushButton* addReviewQPushButton;

	//view cart Window
	QWidget* userCartWidget;
	QVBoxLayout* userCartLayout;
	QListWidget* productCartListWidget;
	std::map<User*, std::list<Product*> > userCarts;
	std::map<std::string, User*> userMap;
	std::list<Product* > cart;
	User* u;

	//buy cart
	QHBoxLayout* buyCartLayout;
	QPushButton* buyCartButton;
	QPushButton* removeItemButton;

	//save database 
	QHBoxLayout* saveDatabaseLayout;
	QLineEdit* filenameInput;
	QPushButton* saveDatabaseButton;
	QPushButton* quitAmazonButton;

};
