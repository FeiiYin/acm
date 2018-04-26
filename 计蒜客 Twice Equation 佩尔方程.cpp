/*
 * @Samaritan_infi
 */
/// https://nanti.jisuanke.com/t/19978
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.*;



public class Main  {
	public static void main(String [] args){
		BigInteger [] x = new BigInteger[30000] ;
		BigInteger [] y = new BigInteger[30000] ;
		BigInteger [] n = new BigInteger[30000] ;
		x[1] = BigInteger.valueOf(7);
		y[1] = BigInteger.valueOf(5);
		n[1] = BigInteger.valueOf(3) ;
		
		BigInteger MAX = BigInteger.valueOf(10) ;
		for(int i = 1 ; i <= 190 ; i ++) MAX = MAX.multiply(BigInteger.valueOf(10)) ;
		
		int pos = 1 ;
		
		while(n[pos].compareTo(MAX) <= 0){
			x[pos + 1] = x[pos].multiply(BigInteger.valueOf(3)).add(
					y[pos].multiply(BigInteger.valueOf(4))) ;
			y[pos + 1] = x[pos].multiply(BigInteger.valueOf(2)).add(
					y[pos].multiply(BigInteger.valueOf(3))) ;
			n[pos + 1] = x[pos].subtract(BigInteger.valueOf(1)).divide(BigInteger.valueOf(2)) ;
			pos ++ ;
		}
		
		Scanner cin = new Scanner(System.in) ;
		int kase = cin.nextInt() ;
		while(kase -- > 0){
			BigInteger temp = cin.nextBigInteger() ;
			int i = 1 ;
			while(temp.compareTo(n[i]) > 0) i ++ ;
			
			System.out.println(n[i]);
		}
		cin.close();
	}
}
