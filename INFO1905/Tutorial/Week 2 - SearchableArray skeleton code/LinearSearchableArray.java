
/*
 * This class signature means:
 * 1) LinearSearchableArray uses a generic type T which must be comparable
 * and
 * 2) LinearSearchableArray extends SearchableArray (with the same comparable type T)
 */
public class LinearSearchableArray<T extends Comparable<T>> extends SearchableArray<T> {

	// constructor
	public LinearSearchableArray(T[] data) {
		super(data); //call the constructor of the super-type as SearchableArray<T>(data)
	}
	
	// implement the abstract method from SearchableArray
	@Override
	public T search(T target) {
		
		int len = this.data.length;
		
		for ( int i = 0; i < len ; i++){
			if ( this.data[i].equals( target ) ){
				return target;
			}
		}
		
		return null; //if the search failed, return null
	}

}
