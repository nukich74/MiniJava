class Factorial{
    public static void main(String[] a){
	System.out.println(new Fac().Compute1(10));
    }
}

class Fac {

    public int Compute1(int num){
		int a;
		int b;
		int c;
        int d;
        int e;
        int f;
        int g;
    	a = 0;
    	c = 0;
        d = 10;
    	b = a + 1;
    	c = c + b;
    	a = b * 2;
        f = b + d;
        e = f + d;
        d = e + c;
        g = a + b;
        g = c + d;
        g = e + f;
        e = a + b;
        e = c + d;
        e = f + g;
        c = a + b;
        c = d + e;
        c = f + g;
        b = c + a;
        b = d + e;
        b = f + g;
        a = f + g;
        c = a + g;
        c = d + e;
        c = f + b;
        b = d + e;
        b = g + f;
        c = b + f;
        d = e + c;
        g = a + b;
        g = c + d;
        g = e + f;
        e = a + b;
        e = c + d;
        e = f + g;
        c = a + b;
    	return c; 
    }

}