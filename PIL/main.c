/*
 * main.c
 */
int main(void) {
	

	//inputs for PIL - I added this in control.h file in npc-solar in tsk.1 structue

	//int16_t VARout_probeV;
	//int16_t VARout_probeF;
	//PIL_OVERRIDE_PROBE(float, s_ref, 0, 1.0, "om");
	//PIL_OVERRIDE_PROBE(float, s, 0, 1.0, "om");
	//PIL_OVERRIDE_PROBE(float, c, 0, 1.0, "A");
	//PIL_READ_PROBE(float, VARout, 0, 1.0, "d");


	//Calibs for PIL - I added this in calib.h file in npc-solar in calibs structure

    //PIL_CALIBRATION(float, s_ref, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, s, 5, 10.0, "", -1000, 1000, 0);

    //PIL_CALIBRATION(float, diff1, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, diff1_1, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, reg_s, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, reg_s_1, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, c, 5, 10.0, "", -1000, 1000, 0);

    //PIL_CALIBRATION(float, diff2, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, diff2_1, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, out, 5, 10.0, "", -1000, 1000, 0);
    //PIL_CALIBRATION(float, out_1, 5, 10.0, "", -1000, 1000, 0);


				//Main regulation Code

				//geting inputs from plecs
				SET_OPROBE(obj->tsk1.s_ref, HAL_getAnalogIn(2, 2));
				SET_OPROBE(obj->tsk1.s, HAL_getAnalogIn(3, 1));
				SET_OPROBE(obj->tsk1.c, HAL_getAnalogIn(3, 2));

				//speed regulation
				Calibs.diff1 = obj->tsk1.s_ref - obj->tsk1.s;
				Calibs.reg_s = Calibs.reg_s_1+5 * Calibs.diff1 - 4.999 * Calibs.diff1_1;
				Calibs.diff1_1 = Calibs.diff1;
				Calibs.reg_s_1 = Calibs.reg_s;

				if(Calibs.reg_s > 150) Calibs.reg_s = 150;
				else if(Calibs.reg_s < -150) Calibs.reg_s = -150;

				//current regulator
				Calibs.diff2 = Calibs.reg_s - obj->tsk1.c;

				Calibs.out=Calibs.out_1+Calibs.diff2-0.9998*Calibs.diff2_1;
				Calibs.diff2_1=Calibs.diff2;
				Calibs.out_1=Calibs.out;

				if(Calibs.out > 1) Calibs.out = 1;
				else if(Calibs.out < -1) Calibs.out = -1;

				// output - duty
				obj->tsk1.VARout = Calibs.out;
				SET_OPROBE(obj->tsk1.VARout, obj->tsk1.VARout);

}
