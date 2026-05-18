#include<iostream>
#include<string>
#include<cmath>
using namespace std;
class IDisplayable {
public:
    virtual void displayDetails() const = 0;
    virtual ~IDisplayable() {}
};
class ISearchable {
public:
    virtual bool matchesQuery(const string& keyword) const = 0;
    virtual ~ISearchable() {}
};
class IReviewable {
public:
    virtual void   addReview(int rating, const string& comment) = 0;
    virtual double getAverageRating() const = 0;
    virtual ~IReviewable() {}
};
class IVerifiable {
public:
    virtual void verify() = 0;
    virtual bool isVerified() const = 0;
    virtual ~IVerifiable() {}
};
class Cardetail {
private:
    int doors;
    string fueltype;
    string transmission;
    bool hasAC;
    string color;
    float fuelavg;
public:
    Cardetail(int d=4, string f="PETROL", string t="MANUAL",bool ac=true, string c="WHITE", float avg=15.0)
        : doors(d),fueltype(f),transmission(t),hasAC(ac), color(c),fuelavg(avg) {}
    void displaycar() const {
        cout<<"Doors : "<<doors<< " | Fuel : "<< fueltype<< " | Trans : "   <<transmission<< " | AC:"<<(hasAC ? "YES" : "NO")<< " | Color:"<<color<< " | Avg:"<<fuelavg<< " km/L"<<endl;
    }

    void checkfuelaverage() const {
        if(fuelavg >= 12.0)
            cout << "  Fuel efficiency GOOD: " << fuelavg << "\n";
        else
            cout << "  Fuel efficiency LOW: "  << fuelavg << "\n";
    }

    void comparecar(const Cardetail& other) const {
        cout << "  Comparing fuel avg: " << fuelavg << " vs " << other.fuelavg << "\n";
        if     (fuelavg > other.fuelavg) 
		cout << "  This car is more fuel efficient.\n";
        else if(fuelavg < other.fuelavg) 
		cout << "  Other car is more fuel efficient.\n";
        else 
		cout << "  Both have same fuel efficiency.\n";
    }

    void calculateResalvalue(double age) const {
        double resale = 3000000 * pow(0.85, age);
        cout<<"Estimated resale after "<<age<<" years: Rs."<<resale<<endl;
    }
    bool operator==(const Cardetail& other) const {
        return fueltype == other.fueltype;
    }
    Cardetail operator+(const Cardetail& other) const {
        Cardetail result = *this;
        result.fuelavg = (fuelavg + other.fuelavg) / 2.0f;
        return result;
    }
    friend ostream& operator<<(ostream& os, const Cardetail& cd);
    friend istream& operator>>(istream& is, Cardetail& cd);
    friend class Vehicle;
};

ostream& operator<<(ostream& out, const Cardetail& cd) {
    out<< "Doors :"<<cd.doors<<" Fuel:"<<cd.fueltype<<" Trans : "<<cd.transmission<<" Avg:"<<cd.fuelavg <<endl;
    return out;
}
istream& operator>>(istream& in, Cardetail& cd) {
    cout<<"  Enter doors: ";     in>>cd.doors;
    cout<<"  Enter fuel type: "; in>>cd.fueltype;
    return in;
}
class Vehicle : public IDisplayable, public ISearchable, public IReviewable {
private:
    const int vehicleid;
    string brand;
    string model;
    int year;
    double price;
    int mileage;
    static int totalvehicles;
    int reviewRatings[10];
    string reviewComments[10];
    int reviewCount;
protected:
    Cardetail cardetail;
public:
    Vehicle(string b, string m, int y, double p, int mi,Cardetail c = Cardetail()): vehicleid(++totalvehicles), brand(b), model(m),year(y), price(p), mileage(mi), reviewCount(0), cardetail(c) {}
    virtual void displayDetails() const override {
        cout<<"VehicleID:"<<vehicleid<< " | "<<brand<< " "<<model<< " | Year : "<<year<< " | Price : Rs."<<price<< " | Mileage : "<<mileage<<" km"<<endl;
        cardetail.displaycar();
    }
    virtual bool matchesQuery(const string& keyword) const override {
        return brand == keyword || model == keyword;
    }
    virtual void addReview(int rating, const string& comment) override {
        if(reviewCount < 10) {
            reviewRatings[reviewCount]  = rating;
            reviewComments[reviewCount] = comment;
            reviewCount++;
            cout<<"  Review added for "<<brand<< " "<<model<<endl;
        } else 
		cout<<"Review limit reached."<<endl;
    }
    virtual double getAverageRating() const override {
        if(reviewCount == 0) return 0.0;
        double sum = 0;
        for(int i = 0; i < reviewCount; i++) sum += reviewRatings[i];
        return sum / reviewCount;
    }
    void checkcondition() const {
        if(mileage < 50000)  
		cout<<"Vehicle condition: GOOD"<<endl;
        else if(mileage < 100000) 
		cout << "Vehicle condition: FAIR"<<endl;
        else                      
		cout << "Vehicle condition: HEAVILY USED"<<endl;
    }
    void displayefficiency() const { cardetail.checkfuelaverage(); }

    void comparewith(const Vehicle& other) const {
        cout<<"Comparing : "<< brand<< " vs "<<other.brand<<endl;
        cardetail.comparecar(other.cardetail);
    }
    void estimateresale(double age) const { cardetail.calculateResalvalue(age); }
    void updatePrice(double p) {
        price = p;
        cout<<"Price updated to Rs."<<price<<endl;
    }
    static void showTotalVehicles() {
        cout << "Total vehicles: " << totalvehicles << "\n";
    }
    bool operator==(const Vehicle& other) const {
        return brand == other.brand && model == other.model;
    }
    bool operator<(const Vehicle& other) const {
        return price < other.price;
    }
    bool operator>(const Vehicle& other) const {
        return price > other.price;
    }
    friend ostream& operator<<(ostream& os, const Vehicle& v);
    friend class Marketplace;
    friend class Admin;
    friend class Listing;
    friend class Buyer;

    virtual ~Vehicle() {}
};
int Vehicle::totalvehicles = 0;

ostream& operator<<(ostream& out, const Vehicle& v) {
    out<<"VehicleID:"<<v.vehicleid<< " "<<v.brand<<" "<<v.model<<" Rs."<<v.price<<endl;
    return out;
}
class Car : public Vehicle {
private:
    int numDoors;
    double bootSpace;
    bool hasSunroof;
public:
    Car(string b, string m, int y, double p, int mi,int doors=4, double boot=400, bool sunroof=false,Cardetail c=Cardetail()): Vehicle(b, m, y, p, mi, c),numDoors(doors), bootSpace(boot), hasSunroof(sunroof) {}
    virtual void displayDetails() const override {
        cout<<"CAR";
        Vehicle::displayDetails();
        cout<<"  NumDoors:"<<numDoors<<" | Boot:"<<bootSpace<<" L"<<" | Sunroof : " <<(hasSunroof ? "YES" : "NO")<<endl;
    }
    void displayDetails(bool showExtended) const {
        displayDetails();
        if(showExtended) {
            cout<<"Extended Avg Rating: "<<getAverageRating()<<endl;
            checkcondition();
        }
    }
    Car operator+(const Car& other) const {
        Car result = *this;
        result.bootSpace = bootSpace + other.bootSpace;
        return result;
    }
};
class Bike : public Vehicle {
private:
    int engineCC;
    string handlebarType;
    bool hasFairing;
public:
    Bike(string b, string m, int y, double p, int mi,int cc=125, string hbar="STANDARD", bool fairing=false,Cardetail c=Cardetail()):Vehicle(b, m, y, p, mi, c),engineCC(cc),handlebarType(hbar),hasFairing(fairing) {}
    virtual void displayDetails() const override {
        cout<<"BIKE";
        Vehicle::displayDetails();
        cout<<"  Engine:"<<engineCC<<" CC"<<" | Handlebar:"<<handlebarType<<" | Fairing:"<<(hasFairing ? "YES" : "NO")<<endl;
    }
    void displayDetails(bool showExtended) const {
        displayDetails();
        if(showExtended)
        cout<<"Extended Avg Rating: "<<getAverageRating()<<endl;
    }
};
class User : public IDisplayable, public IVerifiable {
private:
    const int userid;
    string name;
    string email;
    string password;
    string phone;
    bool verified;
    static int totalusers;
public:
    User():userid(++totalusers), name("NA"), email("NA"),password("NA"),phone("NA"),verified(false) {}

    User(string n, string e, string pass, string ph):userid(++totalusers), name(n), email(e),password(pass), phone(ph), verified(false) {}
    User(const User& u):userid(u.userid), name(u.name), email(u.email),password(u.password), phone(u.phone), verified(u.verified) {}
    void login()  { cout << name << " LOGGED IN\n"; }
    void logout() { cout << name << " LOGGED OUT\n"; }
    void updateprofile(string n, string ph) {
        name  = n;
        phone = ph;
        cout<<"Profile updated : "<<name<<" | "<<phone<<endl;
    }
    virtual void displayDetails() const override {
        cout<<"UserID:"<<userid<<" | Name : "<<name<<" | Email : "<<email<<" | Phone : "<<phone<<" | Verified : "<<(verified ? "YES" : "NO")<<endl;
    }
    virtual void verify() override {
        verified = true;
        cout << name << "has been verified "<<endl;
    }
    virtual bool isVerified() const override { return verified; }
    static void showTotalUsers() {
        cout<<"Total users : "<<totalusers<<endl;
    }
    bool operator==(const User& other) const {
        return userid == other.userid;
    }
    friend ostream& operator<<(ostream& out, const User& u);
    friend void compareUsers(const User& a, const User& b);
    friend class Admin;
    friend class Message;
    friend class Marketplace;
    virtual ~User() {}
};
int User::totalusers = 0;
ostream& operator<<(ostream& out, const User& u) {
    out<<"UserID : "<<u.userid<<" "<<u.name<<" " <<u.email<<endl;
    return out;
}
void compareUsers(const User& a, const User& b) {
    cout<<"Comparing: "<<a.name<<" (ID:" << a.userid<< ") vs "<<b.name<<"(ID:" << b.userid << ")"<<endl;
    if(a.userid < b.userid) 
	cout<<a.name<<"joined earlier"<<endl;
    else                    
	cout<<b.name <<" joined earlier"<<endl;
}
class Listing;
class Seller;
class Buyer : public User, public IReviewable {
private:
    double budget;
    Vehicle* favorites[5];
    int favcount;
    const int maxfav;
    int reviewRatings[10];
    string reviewComments[10];
    int reviewCount;
public:
    Buyer(): User(), budget(0), favcount(0), maxfav(5), reviewCount(0) {}
    Buyer(string n, string e, string pass, string ph, double b):User(n, e, pass, ph), budget(b),favcount(0), maxfav(5), reviewCount(0) { verify(); }
    virtual void displayDetails() const override {
        cout<<"BUYER";
        User::displayDetails();
        cout<<"  Budget: Rs."<<budget<<endl;
    }
    virtual void addReview(int rating, const string& comment) override {
        if(reviewCount < 10) {
            reviewRatings[reviewCount]  = rating;
            reviewComments[reviewCount] = comment;
            reviewCount++;
            cout<<"Buyer "<<*this<<" added a review"<<endl;
        }
    }
    virtual double getAverageRating() const override {
        if(reviewCount == 0) return 0.0;
        double sum = 0;
        for(int i = 0; i < reviewCount; i++) sum += reviewRatings[i];
        return sum / reviewCount;
    }
    void addFavorite(Vehicle* v) {
        if(favcount < maxfav) {
            favorites[favcount++] = v;
            cout<<"Vehicle "<<*v<<" added to favorites"<<endl;
        } else cout << "Favorites full.\n";
    }
    void viewFavorites() const {
        cout<<"Favorites for "<<*this<<endl;
        for(int i = 0; i < favcount; i++) favorites[i]->displayDetails();
    }
    void searchVehicleByPrice(Vehicle* vehicles[], int total, double maxPrice) const {
        cout<<"Searching vehicles under Rs."<<maxPrice<<endl;
        for(int i = 0; i < total; i++)
            if(vehicles[i]->price <= maxPrice) 
                vehicles[i]->displayDetails();
    }
    void sendmessage(Seller* s, const string& content);
    bool operator<(const Buyer& other) const {
        return budget < other.budget;
    }
};
class Seller : public User, public IReviewable {
private:
    Listing*  listings[5];
    int listingcount;
    double rating;
    const string role;
    int reviewRatings[10];
    string reviewComments[10];
    int reviewCount;
public:
    Seller(): User(), listingcount(0), rating(5.0),role("Seller"), reviewCount(0) {}

    Seller(string n, string e, string pass, string ph, double r): User(n, e, pass, ph), listingcount(0),rating(r), role("Seller"), reviewCount(0) { verify(); }
    virtual void displayDetails() const override {
        cout<<"SELLER";
        User::displayDetails();
        cout<<"Rating : " << rating<<" | Listings : "<<listingcount<<endl;
    }
    virtual void addReview(int rating, const string& comment) override {
        if(reviewCount < 10) {
            reviewRatings[reviewCount]  = rating;
            reviewComments[reviewCount] = comment;
            reviewCount++;
            cout<<"Seller "<<*this<<" received a review"<<endl;
        }
    }
    virtual double getAverageRating() const override {
        if(reviewCount == 0) return 0.0;
        double sum = 0;
        for(int i = 0; i < reviewCount; i++) sum += reviewRatings[i];
        return sum / reviewCount;
    }
    void updateRating(double r) {
        rating = r;
        cout<<"Seller rating updated to "<<rating<<endl;
    }
    void addListing(Listing* l);
    void viewListings() const;
    void updateListingPrice(int idx, double newPrice);
    void deleteListing(int idx);
    bool operator>(const Seller& other) const {
        return rating > other.rating;
    }
};
class Admin : public User {
private:
    int level;
    bool superadmin;
    const string role;
    static int totaladmins;
public:
    Admin(): User(), level(1), superadmin(false),role("Admin") { totaladmins++; }

    Admin(string n, string e, string pass, string ph, int lvl): User(n, e, pass, ph), level(lvl),superadmin(true), role("Admin") { totaladmins++; verify(); }
    virtual void displayDetails() const override {
        cout<<"ADMIN";
        User::displayDetails();
        cout<<" Level:"<<level<< " | SuperAdmin:"<<(superadmin ? "YES" : "NO")<<endl;
    }
    void approveListing(Listing* l);
    void removeListing(Listing* l);
    void banUser(User* u) {
        cout<<"User "<<u->name<<" has been banned by Admin."<<endl;
    }
    void viewReports() const {
        cout<<"Viewing all marketplace reports"<<endl;
    }
    void auditVehicle(const Vehicle& v) const {
        cout<<"ADMIN AUDIT VehicleID : "<< v.vehicleid<<" Brand : " << v.brand<<" Price : Rs."<<v.price<<endl;
    }
    static void showAdmins() {
        cout<<"Total Admins : "<<totaladmins<<endl;
    }
};
int Admin::totaladmins = 0;
class Listing : public IDisplayable, public ISearchable {
private:
    const int listingid;
    Vehicle* vehicle;
    string city;
    string status;
    string postDate;
    static int totallistings;

public:
    Listing(Vehicle* v, string c, string d):listingid(++totallistings), vehicle(v),city(c), postDate(d) {
        status = "Pending";
    }
    virtual void displayDetails() const override {
        cout<<"Listing ID:"<<listingid<<endl;
        vehicle->displayDetails();
        cout<<"City:"<<city<<" | Status:"<<status<<" | Posted:"<<postDate<<endl;
    }
    virtual bool matchesQuery(const string& keyword) const override {
        return city == keyword || vehicle->matchesQuery(keyword);
    }
    void approveListing() {
        status = "Approved";
        cout<<"Listing "<<listingid<<" approved"<<endl;
    }
    void removeListing() {
        status = "Removed";
        cout<<"Listing "<<listingid<<" removed"<<endl;
    }
    void updateListing(double newPrice) {
        vehicle->updatePrice(newPrice);
        cout<<"Listing "<<listingid<<" price updated to Rs."<<newPrice<<endl;
    }
    bool operator==(const Listing& other) const {
        return city == other.city;
    }
    friend ostream& operator<<(ostream& out, const Listing& l);
    friend class Marketplace;
    friend class Seller;
    friend class Admin;
};
int Listing::totallistings = 0;

ostream& operator<<(ostream& out, const Listing& l) {
    out<<"ListingID:"<<l.listingid<<" City:"<< l.city<<" Status:"<<l.status<<endl;
    return out;
}
void Seller::addListing(Listing* l) {
    if(listingcount < 5) {
        listings[listingcount++] = l;
        cout<<"Listing "<<l->listingid<<" added by seller "<<*this<<endl;
    } else
	  cout<< "Cannot add more listings"<<endl;
}
void Seller::viewListings() const {
    cout<<"Listings by "<<*this<<endl;
    for(int i = 0; i < listingcount; i++) listings[i]->displayDetails();
}
void Seller::updateListingPrice(int idx, double newPrice) {
    if(idx < listingcount) listings[idx]->updateListing(newPrice);
}
void Seller::deleteListing(int idx) {
    if(idx < listingcount) {
        listings[idx]->removeListing();
        for(int i = idx; i < listingcount-1; i++) listings[i] = listings[i+1];
        listingcount--;
    }
}
void Admin::approveListing(Listing* l) { l->approveListing(); }
void Admin::removeListing(Listing* l)  { l->removeListing();  }
class Message {
private:
    const int messageid;
    static int totalmessages;
    User* sender;
    User* receiver;
    string content;
    bool seen;
public:
    Message(User* s, User* r, const string& c): messageid(++totalmessages), sender(s),receiver(r), content(c), seen(false) {}
    void send() {
        cout<<"Message from " << sender->name<<" to "<<receiver->name<< ": "<<content<<endl;
    }
    void markSeen() {
        seen = true;
        cout<<"Message "<<messageid<<" marked as seen"<<endl;
    }
    void deleteMessage() {
        cout<<"Message "<<messageid<<" deleted"<<endl;
    }
    void display() const {
        cout<<"MsgID:"<<messageid<<" | From:"<<sender->name<<" | To:"<<receiver->name<< " | Seen:"<<(seen ? "YES" : "NO")<< " | "<<content<<endl;
    }
    bool operator==(const Message& other) const {
        return messageid == other.messageid;
    }
};
int Message::totalmessages = 0;
void Buyer::sendmessage(Seller* s, const string& content) {
    Message m(this, s, content);
    m.send();
}
class Review : public IDisplayable {
private:
    const int reviewid;
    Vehicle* vehicle;
    Buyer* reviewer;
    int rating;
    string comment;
    static int totalreviews;
public:
    Review(Vehicle* v, Buyer* b, int r, string c): reviewid(++totalreviews), vehicle(v),reviewer(b), rating(r), comment(c) {}
    virtual void displayDetails() const override {
        cout<<"ReviewID:"<<reviewid<<" | Vehicle:" <<*vehicle<<" | Buyer:"<<*reviewer<<" | Rating:"<<rating<< " | "<<comment<<"\n";
    }
    void updateRating(int r) {
        rating = r;
        cout<<"Rating updated to "<<rating<<" for Review "<<reviewid<<endl;
    }
    void updateComment(const string& c) {
        comment = c;
        cout<<"Comment updated for Review "<<reviewid<<endl;
    }
    void deleteReview() {
        cout<<"Review "<<reviewid<<" deleted"<<endl;
    }
    bool operator>(const Review& other) const {
        return rating > other.rating;
    }
    friend ostream& operator<<(ostream& out, const Review& r);
    friend void printReviewSummary(const Review& r);
    static void showTotalReviews() {
        cout<<"Total Reviews: "<< totalreviews<<endl;
    }
};
int Review::totalreviews = 0;
ostream& operator<<(ostream& out, const Review& r) {
    out<<"ReviewID:"<<r.reviewid<<" Rating:"<<r.rating<<" Comment:"<<r.comment<<endl;
    return out;
}
void printReviewSummary(const Review& r) {
    cout<<"SUMMARY ReviewID:"<<r.reviewid<<" | Stars: "<<r.rating<< "/5"<<" | Note: "<<r.comment<<endl;
}
class Marketplace {
private:
    const string platformname;
    User* users[20];
    Listing* listings[20];
    int usercount;
    int listingcount;
    string location;

public:
    Marketplace(string loc): platformname("PakWheels Clone"), location(loc),usercount(0), listingcount(0) {}
    void addUser(User* u) {
        if(usercount < 20) {
            users[usercount++] = u;
            cout<<"User "<<u->name<<" added to marketplace"<<endl; 
        } else 
		cout<<"User limit reached"<<endl;
    }

    void addListing(Listing* l) {
        if(listingcount < 20) {
            listings[listingcount++] = l;
            cout<<"Listing "<<l->listingid<<" added"<<endl;       
        } else 
		cout<<"Listing limit reached"<<endl;
    }
    void displayAllListings() const {
        cout<<"All Marketplace Listings";
        for(int i = 0; i < listingcount; i++)
            listings[i]->displayDetails();
    }
    void searchVehicle(double maxPrice) const {
        cout<<"Vehicles under Rs."<<maxPrice<<endl;
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->vehicle->price <= maxPrice) { 
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"None found"<<endl;
    }
    void filterByCity(string cityname) const {
        cout<<"Listings in " << cityname<<endl;
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->city == cityname) {             
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"None found in "<< cityname<<endl;
    }
    void approveAllPending() {
        cout<<"\nApproving all pending listings...";
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->status == "Pending")            
                listings[i]->approveListing();
    }
    void searchbybrand(string b) const {
        cout<<"\nSearching by brand : "<<b<<endl;
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->vehicle->brand == b) {          
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"No vehicle found for brand : "<<b<<endl;
    }
    void searchbymodel(string m) const {
        cout<<"\nSearching by model : "<<m<<endl;
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->vehicle->model == m) {         
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"No vehicle found for model : "<<m<<endl;
    }
    void searchbyyear(int yr) const {
        cout<<"\nSearching by year: "<<yr<<endl;
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->vehicle->year == yr) {          
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"No vehicle found for year : "<<yr<<endl;
    }
    void searchbymileage(int maxMileage) const {
        cout<<"\nVehicles under "<<maxMileage<<" km:\n";
        bool found = false;
        for(int i = 0; i < listingcount; i++)
            if(listings[i]->vehicle->mileage <= maxMileage) { 
                listings[i]->displayDetails(); found = true;
            }
        if(!found) cout<<"No vehicle found under mileage: "<<maxMileage<<endl;
    }
    int operator+(const Marketplace& other) const {
        return listingcount + other.listingcount;
    }
    bool operator==(const Marketplace& other) const {
        return location == other.location;
    }
};
int main() {
    cout<<"Car Market Place "<<endl;
    cout<<"Cardetail Operator Overloading"<<endl;
    Cardetail cd1(4,"PETROL","MANUAL",true,"RED",14.0);
    Cardetail cd2(2,"DIESEL","AUTOMATIC",true,"BLACK",10.0);
    Cardetail cd3(4,"PETROL","MANUAL",false,"BLUE",13.0);

    cout<<"CD1: "<<cd1<<endl;
    cout<<"CD2: " <<cd2<<endl;
    cout<<"(same fuel type)?"<<(cd1 == cd3 ? "YES" : "NO")<<endl;
    Cardetail cdAvg = cd1 + cd2;
    cout<<"Average of CD1 + CD2 : "<<cdAvg<<endl;
    
    cout << "Vehicle Polymorphism (Car & Bike)"<<endl;
    Car  car1("Toyota","Corolla",2019,3000000,40000,4,450,false,cd1);
    Car  car2("Honda","Civic",2018,2500000,90000,4,400,true,cd2);
    Bike bike1("Yamaha","YBR125",2021,200000,15000,125,"STANDARD",false);
    Bike bike2("Honda","CB150F",2022,250000,10000,150,"SPORT",true);

    Vehicle* vehicles[4] = { &car1, &car2, &bike1, &bike2 };
    for(int i = 0; i < 4; i++)
        vehicles[i]->displayDetails();  
    cout<<"Function Overloading on Car "<<endl;
    car1.displayDetails(true);

    cout<<"Vehicle Operator Overloading"<<endl;
    cout<<"car1 == car2? "<<(car1 == car2 ? "YES" : "NO")<<endl;
    cout<<"car1 > car2 (price)? "<<(car1 > car2  ? "YES" : "NO")<<endl;
    cout<<"car2 < car1 (price)? "<<(car2 < car1  ? "YES" : "NO")<<endl;
    cout<<"car1 via <<: "<< car1 <<endl;

    cout<<" IReviewable on Vehicle"<<endl;
    car1.addReview(5, "Excellent ride!");
    car1.addReview(4, "Good condition.");
    cout<<"Car1 avg rating: "<<car1.getAverageRating()<<endl;
    cout<<"ISearchable"<<endl;
    cout<<"car1 matches 'Toyota'? "<<(car1.matchesQuery("Toyota") ? "YES" : "NO")<<endl;
    cout<<"bike1 matches 'Honda'? "<<(bike1.matchesQuery("Honda") ? "YES" : "NO")<<endl;
    cout<<"User Polymorphism (Buyer, Seller, Admin)"<<endl;
    Buyer  b1("Ahmed","ahmed@mail.com","abc123","0300111222",3500000);
    Buyer  b2("Fatima","fatima@mail.com","fat123","0300333444",2000000);
    Seller s1("Hassan","hassan@mail.com","pass456","0300222333",4.5);
    Admin  a1("Admin1","admin@mail.com","adminpass","0300999888",2);
    User* users[4] = { &b1, &b2, &s1, &a1 };
    for(int i = 0; i < 4; i++) users[i]->displayDetails();  

    cout<<"User Operator Overloading"<<endl;
    cout<<"b1 == b2?  "<<(b1 == b2 ? "YES" : "NO")<<endl;
    cout<<"b1 via <<: "<< b1 <<endl;

    Seller s2("Zara","zara@mail.com","zara123","0300555666",3.8);
    cout<<"s1 > s2 (rating)? "<<(s1 > s2 ? "s1 higher" : "s2 higher")<<endl;
    cout<<"b1 < b2 (budget)? "<<(b1 < b2 ? "YES" : "NO")<<endl;
    cout<<"Friend Function 1: compareUsers";
    compareUsers(b1, s1);
    cout<<"Listings"<<endl;
    Listing l1(&car1,"Karachi","2026-03-01");
    Listing l2(&car2,"Lahore","2026-03-02");
    Listing l3(&bike1,"Karachi","2026-03-10");
    Listing l4(&bike2,"Islamabad","2026-03-12");
    l1.displayDetails();
    l2.displayDetails();
    cout<<"Listing Operator Overloading"<<endl;
    cout<<"l1 == l3 (same city)? "<<(l1 == l3 ? "YES" : "NO")<<endl;
    cout<<"l1 via <<: "<< l1 <<endl;
    cout<<"Marketplace"<<endl;
    Marketplace market("Pakistan");
    market.addUser(&b1);
    market.addUser(&b2);
    market.addUser(&s1);
    market.addListing(&l1);
    market.addListing(&l2);
    market.addListing(&l3);
    market.addListing(&l4);

    market.displayAllListings();
    market.searchVehicle(2600000);
    market.filterByCity("Karachi");
    market.approveAllPending();
    market.searchbybrand("Toyota");
    market.searchbyyear(2021);
    market.searchbymileage(20000);
    Marketplace market2("India");
    cout<<"market == market2? "<<(market == market2 ? "YES" : "NO")<<endl;
    cout<<"Total listings (market+market2): "<<(market + market2) <<endl;
    cout<<"Seller Operations"<<endl;
    s1.addListing(&l1);
    s1.addListing(&l2);
    s1.viewListings();
    s1.updateListingPrice(0, 3200000);
    s1.addReview(5, "Trusted seller!");
    cout<<"Seller avg rating: " << s1.getAverageRating() << "\n";
    cout<<"Buyer Operations"<<endl;
    b1.addFavorite(&car1);
    b1.addFavorite(&bike1);
    b1.viewFavorites();
    Vehicle* allV[4] = { &car1, &car2, &bike1, &bike2 };
    b1.searchVehicleByPrice(allV, 4, 2600000);
    b1.sendmessage(&s1, "Is the Corolla still available?");
    cout<<"Admin Operations"<<endl;
    a1.approveListing(&l3);
    a1.removeListing(&l4);
    a1.banUser(&b2);
    a1.viewReports();
    a1.auditVehicle(car1);
    Admin::showAdmins();
    cout<<"Messaging"<<endl;
    Message m1(&b1, &s1, "What is the final price?");
    m1.send();
    m1.markSeen();
    m1.display();
    m1.deleteMessage();
    cout<<"Message Operator Overloading"<<endl;
    Message m2(&b2, &s1, "Is the bike available?");
    cout<<"m1 == m2? "<< (m1 == m2 ? "YES" : "NO")<<endl;
    cout << "\n--- Reviews ---\n";
    Review r1(&car1, &b1, 5, "Excellent condition, smooth drive!");
    Review r2(&car2, &b1, 3, "Average, needed servicing.");
    r1.displayDetails();
    r2.displayDetails();
    cout<<"Review Operator Overloading"<<endl;
    cout<<"r1 > r2? "<<(r1 > r2 ? "YES" : "NO")<<endl;
    cout<<"r1 via <<: "<<r1<<endl;
    cout<<"Friend Function 3: printReviewSummary"<<endl;
    printReviewSummary(r1);
    printReviewSummary(r2);
    r1.updateRating(4);
    r1.updateComment("Good car, minor scratches.");
    r1.deleteReview();
    Review::showTotalReviews();
    cout<<"IVerifiable Demo"<<endl;
    cout<<"b1 verified? "<<(b1.isVerified() ? "YES" : "NO")<<endl;
    cout<<"s1 verified? " <<(s1.isVerified() ? "YES" : "NO")<<endl;
    cout<<"ISearchable on Listing"<<endl;
    cout<<"l1 matches 'Karachi'? "<<(l1.matchesQuery("Karachi") ? "YES" : "NO")<<endl;
    cout<<"l2 matches 'Yamaha'?  "<<(l2.matchesQuery("Yamaha")  ? "YES" : "NO")<<endl;
    User::showTotalUsers();
    Vehicle::showTotalVehicles();
    return 0;
}
