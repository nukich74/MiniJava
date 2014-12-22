// The classes are basically the same as the BinaryTree 
// file except the visitor classes and the accept method
// in the Tree class

class TreeVisitor {
    public static void main(String[] a){
	System.out.println(new TV().Start());
    }
}

class TV extends MyVisitor {

}


class Tree extends TV {

}

  

class Visitor extends Tree {

}


class MyVisitor extends Visitor {

}
