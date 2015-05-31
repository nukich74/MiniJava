class Factorial{
    public static void main(String[] a){
	System.out.println(new Fac().ComputeFac(10));
    }
}

class Fac {

    public int ComputeFac(int num){
		int a;
		int b;
		int c;
    	a = 0;
    	c = 0;
    	b = a + 1;
    	c = c + b;
    	a = b * 2;
    	return c;
    }

}