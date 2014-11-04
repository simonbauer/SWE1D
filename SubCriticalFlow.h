/**
 * This is a scenario to solve Exercise 2.1 of Assignment 2 
 * SUBCRITICAL FLOW
 */
namespace scenarios
{

class SubCriticalFlow{
private:
	/** Number of cells */
		const unsigned int m_size;


  public:
	SubCriticalFlow(unsigned int size)
		: m_size(size)
	{
	}

  	// get the bathymerty at Position x 
  	// Formula (6)
    float getBathymetry(float x) {
    	if(x < 12 && x > 8)
       		return (-1.8-0.05*((x-10)*(x-10))) ;
       	else
       		return -2;
    };

    // get the waterheight at Position x

    float getHeight(float x) {

    	return -getBathymetry(x);
      	/* if(x < 12 && x > 8)
       		return (-(-1.8-0.05*((x-10)*(x-10)))) ;
       	else
       		return 2;*/

    };


    // get the velocity at Position x

	 float getVelocity(float x) {

	 	return 4.42/getHeight(x);

	 };
	 /**
	 * @return Cell size of one cell (= domain size/number of cells)
	 */
	 T getCellSize()
	 {
	    return 1000.f / m_size;
	 }
};
}
/* get the number of timesteps for the current scenario

	 float getTimesteps() {

	 	return 200;

	 }*/


    
   
