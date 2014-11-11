#include<iostream>
#include<vector>
#include<string>

using namespace std;



__interface Visitor {
public:
  void visit(Program n);
  void visit(MainClass n);
  void visit(Identifier n);
};


__interface TypeVisitor {
  Type* visit(Program n);
  Type* visit(MainClass n); 
  Type* visit(Identifier n);
};




__interface Type {
  virtual void accept(Visitor* v) = 0;
  virtual Type* accept(TypeVisitor* v) = 0;
};


__interface Exp {
public:
	virtual void accept(Visitor* v) = 0;
	virtual Type* accept(TypeVisitor* v) = 0;
};

 __interface Statement {
 public:
	virtual void accept(Visitor* v) = 0;
	virtual Type* accept(TypeVisitor* v) = 0;
};


 __interface ClassDecl {
public:
	virtual void accept(Visitor* v) = 0;
    virtual Type* accept(TypeVisitor* v);
};




class Identifier {
public:
	  string s;

	  Identifier(string as) { 
			s=as;
	  }

	  void accept(Visitor* v) {
		  v->visit(*this);
	  }

	  Type* accept(TypeVisitor* v) {
		return v->visit(*this);
	  }

	  string toString(){
		return s;
	  }
};






class ClassDeclList {
public:
   vector<ClassDecl*> list;

   ClassDeclList() {
	   list = std::vector<ClassDecl*>();
   }

   void addElement(ClassDecl* n) {
	   list.push_back(n);
   }

   
   ClassDecl* elementAt(int i)  { 
      return (ClassDecl*)list[i]; 
   }
   

   int size() { 
      return list.size(); 
   }
};



class ExpList {
public:
   vector<Exp*> list;

   ExpList() {
      list = std::vector<Exp*>();
   }

   void addElement(Exp* n) {

	   list.push_back(n);
   }


   
   Exp* elementAt(int i)  { 
      return (Exp*)list[i]; 
   }
   

   int size() { 
      return list.size(); 
   }
};



class MainClass {
public:
	Identifier* i1;
	Identifier* i2;
	Statement* s;

	MainClass(Identifier* ai1, Identifier* ai2, Statement* as) {
		i1=ai1;
		i2=ai2; 
		s=as;
	}

	void accept(Visitor* v) {
		v->visit(*this);
	}

	Type* accept(TypeVisitor* v) {
		return v->visit(*this);
  }
};



class Program {
  
	MainClass m;
	ClassDeclList cl;

	Program( MainClass am, ClassDeclList acl ) {
		m=am; cl=acl; 
		}

	void accept(Visitor* v) {
		v->visit(*this);
	}

	Type* accept(TypeVisitor* v) {
		return v->visit(*this);
	}
};


class Formal {
public:
	Type* t;
	Identifier i;
 
	Formal(Type* at, Identifier ai) {
		t=at;
		i=ai;
	}

	void accept(Visitor* v) {
		v->visit(*this);
	}

	Type* accept(TypeVisitor* v) {
		return v->visit(*this);
	}
};


class FormalList {
private:

	std::vector<Formal> list;
public:
	FormalList(){

	}

   void addElement(Formal n) {
	   list.push_back(n);
   }

   Formal elementAt(int i)  { 
      return (Formal)list[i]; 
   }

   
	int size() { 
      return list.size(); 
   }
};


class MethodDecl {
public:
	Type* t;
	Identifier i;
	FormalList fl;
	VarDeclList vl;
	StatementList sl;
	public Exp e;

	MethodDecl(Type* at, Identifier ai, FormalList afl, VarDeclList avl, 
				StatementList asl, Exp ae) {
		t=at; 
		i=ai; 
		fl=afl; 
		vl=avl; 
		sl=asl; 
		e=ae;
	}
 
	void accept(Visitor* v) {
		v->visit(*this);
	}

	Type* accept(TypeVisitor* v) {
		return v->visit(*this);
	}
};




