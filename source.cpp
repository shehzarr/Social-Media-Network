
#include<iostream>
#include<conio.h>
#include<string>
#include<fstream>
	using namespace std;

class Object;
class Page;
class User;
class Facebook;
class date;
class Post;
class comment;

class Object
{
private:
	char* id;

public:
	void Set_ID(char* str);
	char* Get_ID();
	~Object()
	{
		if (id != 0)
			delete[] id;
		id = NULL;
	}
};

class date
{

private:
	int Date = 0; int Month = 0; int Year = 0;

public:

	date()
	{
		Date = Month = Year = 0;
	}
	date(int d, int m, int y)
	{
		cout << "Command:\t Set current System Date " << d << " " << m << " " << y << endl;
		cout << "System Date:\t ";
		Date = d;
		Month = m;
		Year = y;
	}
	int Get_Date()
	{
		return this->Date;
	}
	int Get_Year()
	{
		return this->Year;
	}
	int Get_Month()
	{
		return this->Month;
	}
	void Set_Date(int d, int m, int y);
	void Display_date();
	void FeedDate(ifstream &fin);
	~date()
	{
		//No pointer of Date have Allocated space
	}
};

class Page : public Object
{
private:

	char* Title;
	Post** Timeline;
	int CountLikes;

public:

	Page();
	~Page()
	{
		if (Title != 0)
		{
			delete[] Title;
			Title = NULL;
		}
		if (Timeline != 0)
		{

			for (int i = 0; Timeline[i] != 0; i++)
			{
				delete Timeline[i];
			}
			delete[] Timeline;
			Timeline = NULL;
		}
	}
	char* GetTitle();
	void SetTitle(char* str);
	void LoadPages(ifstream& fin);
	void PrintPages()
	{
		cout << Get_ID() << Title << endl;
	}
	void AddPostToTimeline(Post*);
	void ViewTimelinePage(User** users, Page** pages, Post** posts);

};

class Post : public Object
{
private:
	char* discription;
	int NoOfLikes;
	date PostDate;
	comment** CommentID;
	Object** SharedBy;
	Object** Likedby;
public:
	Post();
	~Post()
	{
		if (discription != 0)
			delete[] discription;
		discription = NULL;
		if (CommentID != NULL)
		{
			for (int i = 0; CommentID[i] != 0; i++)
			{
				delete[] CommentID[i];
			}
			delete[] CommentID;
			CommentID = NULL;
		}

		if (SharedBy != 0)
			delete[] SharedBy;
		SharedBy = NULL;
		if (Likedby != 0)
			delete[] Likedby;
		Likedby = NULL;
	}
	char* Get_SharedBy(int i)
	{
		return SharedBy[i]->Get_ID();
	}
	char* Get_disc()
	{
		return discription;
	}
	void Set_SharedBy();
	void Set_likedBy();
	void AddLike(User* CurrentUser);
	void CreateComment(char* text, User* CurrentUser);
	int Get_PostDate();
	void Add_Sharer(User* CurrentUser);
	void SetPost(char* str, date CurrentDate, User* CurrentUser);
	void Allocate_ComID()
	{
		if (CommentID == 0)
		{

			CommentID = new comment*[10];
			for (int i = 0; i < 10; i++)
			{
				CommentID[i] = 0;
			}

		}
	}
	void Set_CommentID(comment* reqcom)
	{
		for (int i = 0; i < 10; i++)
		{
			if (CommentID[i] == 0)
			{
				CommentID[i] = reqcom;
				break;
			}
		}
	}
	void LoadPost(ifstream &fin, User**, Page**);
	User* PCheckUser(User** Users, char* str, int Total_Users);
	Page* PCheckPage(Page** page, char* str, int Total_Page);
	void DisplayLikers(char* PostID, User** users, Page** pages);
	void DisplayPost(User** users, Page** pages, Post** posts);

};

class comment : public Object
{
private:
	char* text;
	Object** WhoComment;
public:
	comment();
	~comment()
	{
		if (text != 0)
			delete[] text;
		text = NULL;
		if (WhoComment != 0)
			delete[] WhoComment;
		WhoComment = NULL;
	}
	void LoadComments(ifstream& fin, User** Users, Page** pages, Post** posts);
	User* comment::ComCheckUser(User** Users, char* str, int Total_Users);
	Page* comment::ComCheckPage(Page** page, char* str, int Total_Page);
	Post* ComCheckPost(Post** posts, char* str);
	void SetComment(char* text, User* CurrentUser);

	void SaveCommentIDs(Post** posts, comment* comments);
	void DisplayComm(User** users, Page** pages);
	void DisplayComment();
};

class User : public Object
{
private:

	char* fname;
	char* lname;
	User** FriendList;
	Page** LikedPages;
	char** friendsIds;
	Post** timeline;

public:

	User();
	User(char* fname0, char* lname0, char** friendlist0, char** pageslist0, char** Timeline0);
	~User();

	void LoadUsers(ifstream& fin);
	void Display_Pages();
	void Display_Friends();
	void SetFriendIds(char*, int);
	char* Get_fname();
	char* Get_lname();

	void Set_fname(char* str);
	void Set_lname(char* str);
	void Add_LikePage(Page* page, int ind);
	void Add_Friends(User** user, int ind);
	User* UCheckUser(User**, char*, int);
	void AddPostToTime(Post*);
	void ViewTimeline(User** users, Page** pages, Post** posts);
};


class Facebook
{
private:
	User * * Users;
	Page** pages;
	Post** posts;
	comment** comments;
	User* CurrentUser;
	date CurrentDate;
	static int Total_Users;
	static int Total_Pages;
	static int Total_Comments;
	static int Total_Posts;
public:
	Facebook();
	~Facebook();
	void SetCurrentUser();
	static int Get_TotalUsers()
	{
		return Total_Users;
	}
	static int Get_TotalPages()
	{
		return Total_Pages;
	}
	static int Get_TotalPost()
	{
		return Total_Posts;
	}
	static void Set_TotalPost(ifstream& fin)
	{
		fin >> Total_Posts;
	}
	static int Get_TotalComments()
	{
		return Total_Comments;
	}
	void SetTimeline();
	void EXE();
	User* CheckUser(char* str);
	Page* CheckPage(char* str);
	Post* CheckPost(char* str);
	void LikePost(char* str);
	void AddComment(char* PostID, char* text);
	void ViewLikedList(char* PostID);
	void ViewPost(char* str);
	void ViewFriendList(char* str1);
	void ViewPageTimeline(char* str2);
	void SharePost(char* PostID);
	void Search(char* ToFind);
	int IfSubString(char*str1, char*str2);
	void ViewHome();
	void FeedData();
	void Interface();
};

int Facebook::Total_Pages = 0; int Facebook::Total_Users = 0; int Facebook::Total_Comments = 0; int Facebook::Total_Posts = 0;


int main()
{
	Facebook fb;
	fb.FeedData();
	fb.SetCurrentUser();
	fb.EXE();


	cout << "\nPress any key to exit..\n";
	_getch();

}
// && MAIN ENDS HERE && 


/////////OBJECT CLASS FUNCTIONS//////////
void Object::Set_ID(char* str)
{
	id = new char[strlen(str) + 1];
	strcpy_s(id, strlen(str) + 1, str);
}
char* Object::Get_ID()
{
	return id;
}



/////////..DATE CLASS FUNCTIONS..//////////
void date::Set_Date(int d, int m, int y)
{
	cout << "Command:\t Set current System Date " << d << " " << m << " " << y << endl;
	cout << "System Date:\t ";
	Date = d;
	Month = m;
	Year = y;
}
void date::FeedDate(ifstream &fin)
{
	fin >> Date;
	fin >> Month;
	fin >> Year;
}
void date::Display_date()
{
	cout << Date << "/" << Month << "/" << Year;
}



//////////..PAGE CLASS FUNCTIONS..///////
Page::Page()
{
	Title = 0;
	Timeline = new Post*[10];
	CountLikes = 0;
	for (int i = 0; i < 10; i++)
	{
		Timeline[i] = 0;
	}
}
char* Page::GetTitle()
{
	return Title;
}
void Page::SetTitle(char* str)
{
	Title = new char[strlen(str) + 1];
	strcpy_s(Title, strlen(str) + 1, str);
}

void Page::LoadPages(ifstream& fin)
{
	char Read[81];
	fin >> Read;
	this->Set_ID(Read);
	fin.getline(Read, 80);
	this->SetTitle(Read);
}
void Page::AddPostToTimeline(Post* p)
{
	for (int i = 0; i < 10; i++)
	{
		if (Timeline[i] == 0)
		{
			Timeline[i] = p;
			Timeline[i + 1] = 0;
			break;
		}
	}
}
void Page::ViewTimelinePage(User** users, Page** pages, Post** posts)
{
	for (int i = 0; Timeline[i] != 0; i++)
	{
		Post* PrintPost = Timeline[i];
		PrintPost->DisplayPost(users, pages, posts);
	}
}


//////..USER CLASS FUNCTIONS..///////////
User::User()
{
	fname = NULL;
	lname = NULL;
	timeline = new Post*[10];
	friendsIds = new char*[10];
	FriendList = new User*[10];
	LikedPages = new Page*[10];
	for (int i = 0; i < 10; i++)
	{
		friendsIds[i] = 0;
		FriendList[i] = 0;
		LikedPages[i] = 0;
		timeline[i] = 0;
	}
}
User::User(char* rhsfname, char* rhslname, char** rhsfriendlist, char** rhspageslist, char** rhsTimeline)
{
	fname = new char[strlen(rhsfname)];
	strcpy_s(fname, strlen(rhsfname), rhsfname);
	lname = new char[strlen(rhslname)];
	strcpy_s(lname, strlen(rhslname), rhslname);
}
User::~User()
{
	if (fname != 0)
		delete[] fname;
	fname = NULL;
	if (lname != 0)
		delete[] lname;
	lname = NULL;
	//FriendList and LikedPages are not deleted by loop beacuse the deletion of double pointer will cause memory leak in Faceboook User**
	if (FriendList != 0)
		delete[] FriendList;
	FriendList = NULL;
	if (LikedPages != 0)
		delete[] LikedPages;
	LikedPages = NULL;
	if (timeline != 0)
	{
		for (int i = 0; timeline[i] != 0; i++)
		{
			delete timeline[i];
		}
		delete[] timeline;
		timeline = NULL;
	}

}
void User::Display_Pages()
{
	for (int i = 0; LikedPages[i] != '\0'; i++)
	{
		LikedPages[i]->PrintPages();
	}
}
void User::Display_Friends()
{

	for (int i = 0; FriendList[i] != 0; i++)
	{
		cout << FriendList[i]->Get_ID() << "\t" << FriendList[i]->Get_fname() << "  " << FriendList[i]->Get_lname() << endl << endl;
	}
}
void User::SetFriendIds(char* id, int k)
{
	friendsIds[k] = new char[strlen(id) + 1];
	for (int i = 0; id[i - 1] != '\0'; i++)
	{
		friendsIds[k][i] = id[i];
	}
}
void User::LoadUsers(ifstream& fin)
{
	char Read[81];
	fin >> Read;
	this->Set_ID(Read);
	fin >> Read;
	this->Set_fname(Read);
	fin >> Read;
	this->Set_lname(Read);
}
void User::Add_LikePage(Page* page, int inda)
{
	LikedPages[inda] = page;
}
void User::Add_Friends(User** user, int TUsers)
{
	int NoOfFriends = 0;
	for (int i = 0; strcmp(friendsIds[i], "-1") != 0; i++)
	{
		FriendList[i] = UCheckUser(user, friendsIds[i], TUsers);
		NoOfFriends++;

	}

	//deleting temporary array of friends
	for (int i = 0; i < NoOfFriends; i++)
	{
		delete[] friendsIds[i];
	}
	delete[] friendsIds;
}
char* User::Get_fname()
{
	return fname;
}
char* User::Get_lname()
{
	return lname;
}
void User::Set_fname(char* str)
{
	fname = new char[strlen(str) + 1];
	strcpy_s(fname, strlen(str) + 1, str);
}
void User::Set_lname(char* str)
{
	lname = new char[strlen(str) + 1];
	strcpy_s(lname, strlen(str) + 1, str);
}
User* User::UCheckUser(User** Users, char* str, int Total_Users)
{
	for (int i = 0; i < Total_Users; i++)
	{
		if (strcmp(Users[i]->Get_ID(), str) == 0)
		{
			return Users[i];
			break;
		}
	}
	return 0;
}
void User::AddPostToTime(Post* p)
{
	for (int i = 0; i < 10; i++)
	{
		if (timeline[i] == 0)
		{
			timeline[i] = p;
			break;
		}
	}
}
void User::ViewTimeline(User** users, Page** pages, Post** posts)
{
	for (int i = 0; timeline[i] != 0; i++)
	{
		Post* PrintPost = timeline[i];
		PrintPost->DisplayPost(users, pages, posts);
	}
}

///////..POST CLASS FUNCTIONS..///////////


Post::Post()
{
	discription = NULL;
	NoOfLikes = 0;
	CommentID = 0;
	SharedBy = 0;
	Likedby = 0;
	CommentID = 0;

}
void Post::Set_SharedBy()
{
	int maxshare = 10;
	SharedBy = new Object*[maxshare];
}
void Post::Set_likedBy()
{
	int maxlikes = 10;
	Likedby = new Object*[maxlikes];
}

void Post::SetPost(char* str, date CurrentDate, User* CurrentUser)
{
	Set_ID("post12");
	int size = strlen(str) + 1;
	Post* AddNewPost = new Post;
	AddNewPost->discription = new char[size];
	strcpy_s(AddNewPost->discription, size, str);
	int d = CurrentDate.Get_Date();
	int m = CurrentDate.Get_Month();
	int y = CurrentDate.Get_Year();
	AddNewPost->PostDate.Set_Date(d, m, y);
	AddNewPost->SharedBy = new Object*;
	AddNewPost->SharedBy[0] = CurrentUser;

	CurrentUser->AddPostToTime(AddNewPost);

}


void Post::LoadPost(ifstream &fin, User** Users, Page** page)
{
	char Read[80];
	fin >> Read;
	Set_ID(Read);
	PostDate.FeedDate(fin);
	fin.getline(Read, 79);
	fin.getline(Read, 79);

	discription = new char[strlen(Read) + 1];
	strcpy_s(discription, strlen(Read) + 1, Read);
	Set_SharedBy();
	fin >> Read;
	if (Read[0] == 'u')
	{
		User* FoundUser = PCheckUser(Users, Read, 20);
		SharedBy[0] = FoundUser;

	}
	else
	{
		Page* FoundPage = PCheckPage(page, Read, 20);
		SharedBy[0] = FoundPage;
	}

	Likedby = new Object*[10];
	int i = 0;
	fin >> Read;
	while (strcmp(Read, "-1") != 0)
	{

		if (Read[0] == 'u')
		{
			User* FoundUser = PCheckUser(Users, Read, 20);
			NoOfLikes++;
			Likedby[i] = FoundUser;

		}
		else
		{
			Page* FoundPage = PCheckPage(page, Read, 20);
			Likedby[i] = FoundPage;
		}
		i++;
		fin >> Read;
	}
	Likedby[i] = 0;

	fin.getline(Read, 79);
	fin.getline(Read, 79);


}

User* Post::PCheckUser(User** Users, char* str, int Total_Users)
{
	for (int i = 0; i < Total_Users; i++)
	{
		if (strcmp(Users[i]->Get_ID(), str) == 0)
		{
			return Users[i];
			break;
		}
	}
	return 0;
}
Page* Post::PCheckPage(Page** page, char* str, int Total_Page)
{
	for (int i = 0; i < Total_Page; i++)
	{
		if (strcmp(page[i]->Get_ID(), str) == 0)
		{
			return page[i];
			break;
		}
	}
	return 0;
}
void Post::AddLike(User* CurrentUser)
{
	if (NoOfLikes < 10)		 //maxlimit=10
	{
		Likedby[NoOfLikes] = CurrentUser;
		Likedby[NoOfLikes + 1] = 0;
		NoOfLikes++;
	}
	else
		cout << "Error:Like Post limit reached\n";

}
void Post::CreateComment(char* text, User* CurrentUser)
{
	if (CommentID == 0)
	{
		CommentID = new comment*[10];
		for (int i = 0; i < 10; i++)
		{
			CommentID[i] = 0;
		}
	}
	for (int i = 0; i<10; i++)
	{
		if (CommentID[i] == 0)
		{
			CommentID[i] = new comment;
			CommentID[i]->SetComment(text, CurrentUser);
			break;
		}
	}
}
void Post::DisplayLikers(char* PostID, User** users, Page** pages)
{
	int i = 0;
	char* str;
	cout << PostID << " Liked by:\n";
	for (; Likedby[i] != 0; i++)
	{
		str = Likedby[i]->Get_ID();
		if (*str == 'u')
		{
			User* TargUser = PCheckUser(users, str, Facebook::Get_TotalUsers());
			cout << str << "-" << TargUser->Get_fname() << " " << TargUser->Get_lname();
		}
		else
		{
			Page* TargPage = PCheckPage(pages, str, Facebook::Get_TotalPages());
			cout << str << TargPage->GetTitle();
		}
		cout << endl;
	}
	if (i == 0)
	{
		cout << "\nNo Users have liked this post\n";
	}
}
void Post::Add_Sharer(User* CurrentUser)
{
	for (int i = 0; i<10; i++)
	{
		if (SharedBy[i] == 0)
		{
			SharedBy[i] = CurrentUser;
		}

	}
}
int Post::Get_PostDate()
{
	return PostDate.Get_Date();
}
void Post::DisplayPost(User** users, Page** pages, Post** posts)
{
	char* str = SharedBy[0]->Get_ID();
	if (*str == 'u')
	{
		User* targuser = PCheckUser(users, str, Facebook::Get_TotalUsers());
		cout << targuser->Get_fname() << " " << targuser->Get_lname() << " Shared:\t ";
	}
	else
	{
		Page* targpage = PCheckPage(pages, str, Facebook::Get_TotalPages());
		cout << targpage->GetTitle() << " Shared:\t ";
	}
	cout << discription << "...(";
	PostDate.Display_date();
	cout << ")\n";
	if (CommentID != 0)
	{

		for (int i = 0; CommentID[i] != 0; i++)
		{
			CommentID[i]->DisplayComm(users, pages);
			cout << endl;
		}
	}
	else
		cout << "\n\t\tNo one wrote to this post yet\n";
	cout << endl << endl << endl;
}



//////..COMMENT CLASS FUNCTIONS..//////
comment::comment()
{
	text = 0;
	WhoComment = new Object*;
	WhoComment[0] = 0;
}

User* comment::ComCheckUser(User** Users, char* str, int Total_Users)
{
	for (int i = 0; i < Total_Users; i++)
	{
		if (strcmp(Users[i]->Get_ID(), str) == 0)
		{
			return Users[i];
			break;
		}
	}
	return 0;
}
Page* comment::ComCheckPage(Page** page, char* str, int Total_Page)
{
	for (int i = 0; i < Total_Page; i++)
	{
		if (strcmp(page[i]->Get_ID(), str) == 0)
		{
			return page[i];
			break;
		}
	}
	return 0;
}
Post* comment::ComCheckPost(Post** posts, char* str)
{
	for (int i = 0; i < Facebook::Get_TotalPost(); i++)
	{
		if (strcmp(posts[i]->Get_ID(), str) == 0)
		{
			return posts[i];
			break;
		}
	}
}
void comment::SetComment(char* str, User* CurrentUser)
{
	WhoComment[0] = CurrentUser;
	text = new char[strlen(str) + 1];
	strcpy_s(text, strlen(str) + 1, str);
}

void comment::LoadComments(ifstream& fin, User** Users, Page** pages, Post** posts)
{
	char Read[200];
	fin >> Read;
	Set_ID(Read);
	fin >> Read;
	Post* FoundPost = this->ComCheckPost(posts, Read);
	if (FoundPost != 0)
	{
		FoundPost->Allocate_ComID();
	}

	fin >> Read;
	if (Read[0] == 'u')
	{
		User* FoundUser = ComCheckUser(Users, Read, 20);
		*WhoComment = FoundUser;

	}
	else
	{
		Page* FoundPage = ComCheckPage(pages, Read, 20);
		*WhoComment = FoundPage;
	}

	fin.getline(Read, 199);
	text = new char[strlen(Read) + 1];
	strcpy_s(text, strlen(Read) + 1, Read);
	comment* reqcom = this;
	FoundPost->Set_CommentID(reqcom);
}
void comment::DisplayComment()
{
	cout << "\n------------------------------\n";
	cout << Get_ID() << endl;
	cout << "Who\t" << WhoComment[0]->Get_ID();
	cout << "\n comment is\t" << text << endl;
}
void comment::DisplayComm(User** users, Page** pages)
{
	char Check[5];
	strcpy_s(Check, 5, WhoComment[0]->Get_ID());
	if (Check[0] == 'u')
	{
		User* PrintUser = ComCheckUser(users, Check, Facebook::Get_TotalUsers());
		cout << "\t\t" << PrintUser->Get_fname() << " " << PrintUser->Get_lname() << " wrote:'" << text << "'";

	}
	if (Check[0] == 'p')
	{
		Page* PrintPage = ComCheckPage(pages, Check, Facebook::Get_TotalPages());
		cout << "\t\t" << PrintPage->GetTitle() << " wrote:'" << text << "'";

	}
}


//////..FACEBOOK CLASS FUNCTIONS..///////
Facebook::Facebook()
{
	Users = 0;
	pages = 0;
	posts = 0;
	comments = 0;
	CurrentUser = 0;
}
Facebook::~Facebook()
{
	if (pages != 0)
	{

		for (int i = 0; i < Total_Pages; i++)
		{
			delete pages[i];
		}
		delete[] pages;
		pages = NULL;
	}
	if (Users != 0)
	{

		for (int i = 0; i < Total_Users; i++)
		{
			delete Users[i];
		}
		delete[] Users;
		Users = NULL;
	}
	posts = NULL;
	CurrentUser = NULL;
}
void Facebook::SetCurrentUser()
{
	char* str = new char[4];
	//cin >> str;
	str = "u7";

	cout << "Command:\t Set current user'" << str << "'\n";
	CurrentUser = CheckUser(str);
	cout << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << " successfully set as a current User" << endl << endl;
}
User* Facebook::CheckUser(char* str)
{
	for (int i = 0; i < Total_Users; i++)
	{
		if (strcmp(Users[i]->Get_ID(), str) == 0)
		{
			return Users[i];
			break;
		}
	}
	return 0;
}
Page* Facebook::CheckPage(char* str)
{
	for (int i = 0; i < Total_Pages; i++)
	{
		if (strcmp(pages[i]->Get_ID(), str) == 0)
		{
			return &*pages[i];
			break;
		}
	}
	return 0;
}
Post* Facebook::CheckPost(char* str)
{
	for (int i = 0; i < Get_TotalPost(); i++)
	{
		if (strcmp(posts[i]->Get_ID(), str) == 0)
		{
			return posts[i];
			break;
		}
	}
}

void Facebook::SetTimeline()
{
	//Timeline of Users
	for (int i = 0; i < Facebook::Get_TotalUsers(); i++)
	{
		for (int j = 0; j < Facebook::Get_TotalPost(); j++)
		{
			if (strcmp(Users[i]->Get_ID(), posts[j]->Get_SharedBy(0)) == 0)
			{
				Users[i]->AddPostToTime(posts[j]);
			}
		}
	}
	//Timeline of Pages
	for (int i = 0; i < Facebook::Get_TotalPages(); i++)
	{
		for (int j = 0; j < Facebook::Get_TotalPost(); j++)
		{
			if (strcmp(pages[i]->Get_ID(), posts[j]->Get_SharedBy(0)) == 0)
			{
				pages[i]->AddPostToTimeline(posts[j]);
			}
		}
	}

}
void Facebook::FeedData()
{
	char Read[200];
	char buffer[80];
	ifstream fin;
	int j;
	fin.open("Project-SocialNetworkPages.txt");
	fin >> Total_Pages;
	fin.getline(buffer, 80);


	pages = new Page*[Total_Pages];
	for (int i = 0; i < Total_Pages; i++)
	{
		pages[i] = new Page;
		pages[i]->LoadPages(fin);
	}
	fin.close();


	fin.open("Project-SocialNetworkUsers.txt");
	fin >> Total_Users;
	fin.getline(buffer, 80);
	Users = new User*[Total_Users];
	for (int i = 0; i < Total_Users; i++)
	{
		j = 0;
		Users[i] = new User;
		Users[i]->LoadUsers(fin);
		int k = 0;
		while (strcmp(Read, "-1") != 0)
		{
			fin >> Read;
			Users[i]->SetFriendIds(Read, k);
			k++;
		}
		fin >> Read;

		while (strcmp(Read, "-1") != 0)
		{
			Page* FoundPage = CheckPage(Read);
			Users[i]->Add_LikePage(FoundPage, j);
			fin >> Read;
			j++;
		}
		Read[0] = '0';
	}
	fin.close();

	for (int i = 0; i < Total_Users; i++)
	{

		Users[i]->Add_Friends(Users, Total_Users);
	}
	fin.close();

	fin.open("Project-SocialNetworkPosts.txt");
	fin >> Total_Posts;
	for (int i = 0; i < 8; i++)
		fin.getline(Read, 80);
	posts = new Post*[Total_Posts];


	for (int i = 0; i <Total_Posts; i++)
	{
		posts[i] = new Post;
		posts[i]->LoadPost(fin, Users, pages);
	}

	fin.close();
	fin.open("Project-SocialNetworkComments.txt");

	fin >> Total_Comments;
	comments = new comment*[Total_Comments];
	fin.getline(Read, 199);
	fin.getline(Read, 199);
	for (int i = 0; i < Total_Comments; i++)
	{
		comments[i] = new comment;
		comments[i]->LoadComments(fin, Users, pages, posts);
	}
	fin.close();

	this->SetTimeline();


}
void Facebook::Interface()
{
	cout << "\n\nCommand: View Friend List\n\n" << "--------------------------------------------------------------------------------------------\n\n";
	cout << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << "-Friend List\n\n" << endl;
	CurrentUser->Display_Friends();

	cout << "--------------------------------------------------------------------------------------------\n\n" << "Command: View Liked Pages\n\n" << "--------------------------------------------------------------------------------------------\n\n";
	cout << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << "-Liked Pages\n\n" << endl;
	CurrentUser->Display_Pages();
	cout << "--------------------------------------------------------------------------------------------\n\n";

	for (int i = 0; i < Total_Posts; i++)
	{
		posts[i]->DisplayPost(Users, pages, posts);
		cout << endl;
	}
}
void Facebook::LikePost(char* PostID)
{
	Post* TargPost = CheckPost(PostID);
	TargPost->AddLike(CurrentUser);
}
void Facebook::AddComment(char* PostID, char* text)
{
	Post* TargPost = CheckPost(PostID);
	TargPost->CreateComment(text, CurrentUser);
}
void Facebook::ViewLikedList(char* PostID)
{
	Post* TargPost = CheckPost(PostID);
	TargPost->DisplayLikers(PostID, Users, pages);
}
void Facebook::ViewPost(char* PostID)
{
	Post* TargPost = CheckPost(PostID);
	TargPost->DisplayPost(Users, pages, posts);
}
void Facebook::ViewFriendList(char* str1)
{
	User* TargUser = CheckUser(str1);
	cout << endl << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << "-Friend list\n";
	TargUser->Display_Friends();
}
void Facebook::ViewPageTimeline(char* str2)
{
	Page* TargPage = CheckPage(str2);
	cout << TargPage->GetTitle() << "'s Timeline:\n";
	TargPage->ViewTimelinePage(Users, pages, posts);
}
void Facebook::SharePost(char* PostID)
{
	Post* TargPost = CheckPost(PostID);
	TargPost->SetPost(TargPost->Get_disc(), CurrentDate, CurrentUser);
	TargPost->Add_Sharer(CurrentUser);
}
int Facebook::IfSubString(char*str1, char*str2)		// serving the same purpose of strstr function
{
	int start = 0;
	int flag = 0;
	int end = strlen(str2);
	for (int i = 0; str1[i] != 0; i++)
	{
		if (str1[i] == str2[0])
		{
			for (int j = i + 1, k = 1; str2[k] != 0; j++, k++)
			{
				if (str1[j] != str2[k])
				{
					flag = 0;
					break;
				}
				else
					flag = 1;
			}
			if (flag == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}
void Facebook::Search(char* ToFind)
{
	cout << "\nPeople having " << ToFind << endl;
	for (int i = 0; i < Total_Users; i++)
	{
		if (IfSubString(Users[i]->Get_fname(), ToFind) == 0 || IfSubString(Users[i]->Get_lname(), ToFind) == 0)
		{
			cout << Users[i]->Get_ID() << "-" << Users[i]->Get_fname() << " " << Users[i]->Get_lname() << endl;
		}
	}
	cout << "\nPages having " << ToFind << endl;
	for (int i = 0; i < Total_Pages; i++)
	{
		if (IfSubString(pages[i]->GetTitle(), ToFind) == 0)
		{
			cout << pages[i]->Get_ID() << " " << pages[i]->GetTitle() << endl;
		}
	}
	cout << "\nPosts having " << ToFind << endl;
	for (int i = 0; i < Total_Posts; i++)
	{
		if (IfSubString(posts[i]->Get_disc(), ToFind) == 0)
		{
			cout << posts[i]->Get_ID() << "-" << posts[i]->Get_SharedBy(0) << " Shared:  " << posts[i]->Get_disc() << endl;
		}
	}
}
void Facebook::ViewHome()
{
	for (int i = 0; i < Total_Posts; i++)
	{
		if (CurrentDate.Get_Date() == posts[i]->Get_PostDate() || CurrentDate.Get_Date() == posts[i]->Get_PostDate() + 1)
		{
			posts[i]->DisplayPost(Users, pages, posts);
		}
	}
}
void Facebook::EXE()
{
	CurrentDate.Set_Date(15, 11, 2017);
	CurrentDate.Display_date();
	cout << "\nCommand:\t View Friend list";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	ViewFriendList(CurrentUser->Get_ID());

	cout << "\nCommand:\t View Liked Pages";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	CurrentUser->Display_Pages();

	cout << "\nCommand:\t View Home";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	ViewHome();

	cout << "\nCommand:\t View TimeLine\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << "'s timeline:";
	CurrentUser->ViewTimeline(Users, pages, posts);

	cout << "\nCommand:\t View LikeList(post5)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	char* str = "post5";
	ViewLikedList(str);

	cout << "\nCommand:\t View LikePost(post5)\n";
	LikePost(str);

	cout << "\nCommand:\t View LikeList(post5)\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	ViewLikedList(str);

	str = "post4";
	cout << "\nCommand:\t PostComment(post4,Good Luck for your result)\n\n";
	AddComment(str, "Good Luck for your result");

	cout << "\nCommand:\t ViewPost(post4)\n";
	ViewPost(str);

	str = "post8";
	cout << "\nCommand:\t PostComment(post8,Thanks for the wished)\n\n";
	AddComment(str, "Thanks for the wishes");

	cout << "\nCommand:\t ViewPost(post8)\n";
	ViewPost(str);

	char* str1 = "u7";
	char* str2 = "p1";
	str = "post5";
	cout << "\nCommand:\t SharePost(post5)\n";
	SharePost(str);

	cout << "\nCommand:\t View TimeLine\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << CurrentUser->Get_fname() << " " << CurrentUser->Get_lname() << "'s timeline:\n";
	CurrentUser->ViewTimeline(Users, pages, posts);

	cout << "\nCommand:\t View Page\n";
	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	ViewPageTimeline(str2);

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t Search Birthday\n";
	Search("Birthday");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	cout << "\nCommand:\t Search Ali\n";
	Search("Ali");

	cout << "\n-------------------------------------------------------------------------------------------------------------\n";
	this->Interface();
}
