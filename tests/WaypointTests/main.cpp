/*! \file       main.cpp
 *  \brief      Tests for the Waypoint class.
 *  \details
 *  \author     Ryan Lober
 *  \version
 *  \date       Feb 2016
 *  \bug
 *  \warning
 *  \copyright  GNU General Public License.
 */
/*
 *  This file is part of TGL (Trajectory Generation Library).
 *  Copyright (C) 2016 Institut des Systèmes Intelligents et de Robotique (ISIR)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "../TglTestTools.hpp"
#include "tgl/Waypoint.hpp"

using namespace tgl;

/*************************************************
*
*   Test definitions
*
* Example test pattern:

class MyTest : public TglTest{
protected:
    TglTestMessage test(){
        WaypointSet wpts;
        // do stuff with wpts
        if // good result
            return TGL_TEST_SUCCESS;
        else // bad result
            return TGL_TEST_FAILURE;
    }
};

*************************************************/

class ConstructorTest : public TglTest{
protected:
    TglTestMessage test(){
        double vec_time = 0.0;
        double disp_time = 0.1;
        double rot_time = 0.2;

        Eigen::VectorXd ones(3); ones << 1, 1, 1;
        Eigen::Displacementd disp(2.0, 2.0, 2.0, 1.0, 0.0, 0.0, 0.0);
        Eigen::Rotation3d rot(1.0, 0.0, 0.0, 0.0);

        Waypoint empty_wpt;
        Waypoint vec_wpt(ones, vec_time);
        Waypoint disp_wpt(disp, disp_time);
        Waypoint rot_wpt(rot, rot_time);

        bool checks = true;
        checks &= empty_wpt.get() == Eigen::VectorXd::Zero(0);
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= vec_wpt.getTime() == vec_time;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}

        checks &= vec_wpt.get() == ones;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= vec_wpt.getTime() == vec_time;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}

        checks &= disp_wpt.get() == ones*2.0;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= disp_wpt.getRotation().w() == Eigen::Rotation3d::Identity().w();
        checks &= disp_wpt.getRotation().x() == Eigen::Rotation3d::Identity().x();
        checks &= disp_wpt.getRotation().y() == Eigen::Rotation3d::Identity().y();
        checks &= disp_wpt.getRotation().z() == Eigen::Rotation3d::Identity().z();
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= disp_wpt.getTime() == disp_time;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}

        checks &= rot_wpt.get() == Eigen::VectorXd::Zero(0);
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= rot_wpt.getRotation().w() == Eigen::Rotation3d::Identity().w();
        checks &= rot_wpt.getRotation().x() == Eigen::Rotation3d::Identity().x();
        checks &= rot_wpt.getRotation().y() == Eigen::Rotation3d::Identity().y();
        checks &= rot_wpt.getRotation().z() == Eigen::Rotation3d::Identity().z();
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}
        checks &= rot_wpt.getTime() == rot_time;
        if(!checks){std::cout << "Failed @ " << __LINE__ - 1 << std::endl;}

        return checks ? TGL_TEST_SUCCESS : TGL_TEST_FAILURE;
    }
};


class OperatorTest : public TglTest{
protected:
    TglTestMessage test(){
        Eigen::VectorXd zeros(3); zeros     << 0, 0, 0;
        Eigen::VectorXd ones(3); ones       << 1, 1, 1;
        Eigen::VectorXd twos(3); twos       << 2, 2, 2;
        Eigen::VectorXd threes(3); threes   << 3, 3, 3;

        Waypoint wpt0(zeros, 0.0);
        Waypoint wpt1(ones, 0.0);
        Waypoint wpt2(twos, 0.0);
        Waypoint wpt3(threes, 0.0);

        bool checks = true;

        checks &= wpt1 == wpt1;
        if(!checks){std::cout << "== operator failed." << std::endl;}
        checks &= ((wpt1 + wpt1) == wpt2);
        if(!checks){std::cout << "+ operator failed." << std::endl;}
        checks &= ((wpt3 - wpt2) == wpt1);
        if(!checks){std::cout << "- operator failed." << std::endl;}
        checks &= ((wpt1 * 2.0) == wpt2);
        if(!checks){std::cout << "* operator failed." << std::endl;}
        checks &= ((wpt2 / 2.0) == wpt1);
        if(!checks){std::cout << "/ operator failed." << std::endl;}

        if (checks) {return TGL_TEST_SUCCESS;}
        else        {return TGL_TEST_FAILURE;}
    }
};

class DimensionCheckTest : public TglTest{
protected:
    TglTestMessage test(){
        Eigen::VectorXd zeros(3); zeros     << 0, 0, 0;
        Eigen::VectorXd ones(3); ones       << 1, 1, 1;
        Eigen::VectorXd twos(2); twos       << 2, 2;

        Waypoint wpt;
        Waypoint wpt0(zeros, 0.0);
        Waypoint wpt1(ones, 0.0);
        Waypoint wpt2(twos, 0.0);

        bool checks = true;
        checks &= (wpt.set(zeros)); // should return OK
        checks &= (wpt0.set(ones)); // should return OK
        checks &= !(wpt1.set(twos)); // should return ERROR

        if (checks) {return TGL_TEST_SUCCESS;}
        else        {return TGL_TEST_FAILURE;}
    }
};

/*************************************************
*
*   main
*
*************************************************/

int main(int argc, char const *argv[])
{
    std::vector<TglTest*> testVector;
    /*****************************************/
    /*
    *   Make sure to add your test to the list
    *   e.g. testVector.push_back(new BlahTest);
    */
    testVector.push_back(new ConstructorTest);
    testVector.push_back(new OperatorTest);
    testVector.push_back(new DimensionCheckTest);

    /*****************************************/
    return runAllTests(testVector);
}
