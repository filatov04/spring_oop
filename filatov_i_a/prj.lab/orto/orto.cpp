#include<iostream>
#include<tuple>
namespace geo2d {
	namespace orto {
		using Coordinate = std::tuple <double, double>;

		class Quad {
		public:
			std::tuple<double, double> first_point;
			std::tuple<double, double> second_point;
			Coordinate centre;

			virtual void Union(Quad* first, Quad* second) {
				double temp_x1, temp_x2, temp_y1, temp_y2;
				if (std::get<0>(first->first_point) >= std::get<0>(second->first_point)) {
					temp_x1 = std::get<0>(second->first_point);
				}
				else {
					temp_x1 = std::get<0>(first->first_point);
				}
				if (std::get<1>(first->first_point) >= std::get<1>(second->second_point)) {
					temp_y1 = std::get<1>(second->first_point);
				}
				else {
					temp_y1 = std::get<1>(first->first_point);
				}
				if (std::get<0>(first->second_point) >= std::get<0>(second->second_point)) {
					temp_x2 = std::get<0>(second->second_point);
				}
				else {
					temp_x2 = std::get<0>(first->second_point);
				}
				if (std::get<1>(first->second_point) >= std::get<1>(second->second_point)) {
					temp_y2 = std::get<1>(second->second_point);
				}
				else {
					temp_y2 = std::get<1>(first->second_point);
				}
				std::get<0>(first->first_point) = temp_x1;
				std::get<1>(first->second_point) = temp_y1;
				std::get<0>(second->first_point) = temp_x2;
				std::get<1>(second->second_point) = temp_y2;
			}
		};
		class Square: public Quad {
			Square(double x1, double y1, double x2, double y2) {
				if ((x1 - x2) != (y1 - y2)) {
					throw std::invalid_argument("");
				}
				else {
					std::get<0>(first_point) = x1;
					std::get<1>(first_point) = y1;

					std::get<0>(second_point) = x2;
					std::get<1>(second_point) = y2;

					std::get<0>(centre) = (x2 - x1) / 2 + x1;
					std::get<1>(centre) = (y2 - y1) / 2 + y1;
				}
			}
				void Union(Quad * first, Quad * second) override {
					double temp_x1, temp_y1, temp_x2, temp_y2;
					if (std::get<0>(first->first_point) >= std::get<0>(second->first_point)) {
						temp_x1 = std::get<0>(second->first_point);
					}
					else {
						temp_x1 = std::get<0>(first->first_point);
					}
					if (std::get<1>(first->first_point) >= std::get<1>(second->first_point)) {
						temp_y1 = std::get<1>(second->first_point);
					}
					else {
						temp_y1 = std::get<1>(first->first_point);
					}

					if (std::get<0>(first->second_point) >= std::get<0>(second->second_point)) {
						temp_x2 = std::get<0>(second->second_point);
					}
					else {
						temp_x2 = std::get<0>(first->second_point);
					}
					if (std::get<1>(first->second_point) >= std::get<1>(second->second_point)) {
						temp_y2 = std::get<1>(second->second_point);
					}
					else {
						temp_y2 = std::get<1>(first->second_point);
					}
					if ((temp_x2 - temp_x1) == (temp_y2 - temp_y1)) {
						std::get<0>(first->first_point) = temp_x1;
						std::get<1>(first->first_point) = temp_y1;
						std::get<0>(first->second_point) = temp_x2;
						std::get<1>(first->second_point) = temp_y2;

						std::get<0>(second->first_point) = temp_x1;
						std::get<1>(second->first_point) = temp_y1;
						std::get<0>(second->second_point) = temp_x2;
						std::get<1>(second->second_point) = temp_y2;
					}
					else {

					}
				}

		};
		class Rect : public Quad  {
			//Rect(double x1)
		};
	}
}
