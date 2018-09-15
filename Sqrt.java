  public static BigInteger sqrt(BigInteger x) {
		
		BigInteger l = BigInteger.ZERO, r = BigInteger.valueOf(2);
		while(true) {
			if (r.multiply(r).compareTo(x)>=0) break;
			l = r;
			r = r.multiply(BigInteger.valueOf(2));
		}
		BigInteger  ret = l; 
		while(l.compareTo(r)<=0) {
			BigInteger mid = l.add(r).divide(BigInteger.valueOf(2));
			if (mid.multiply(mid).compareTo(x)<=0) {
				ret = mid ;
				l = mid.add(BigInteger.ONE);
			}else {
				r = mid.subtract(BigInteger.ONE);
			}
		}
		return ret;
	}
