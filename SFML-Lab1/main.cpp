#include <SFML/Graphics.hpp>
#include "TransformNode.h"

int main(int argc, char* argv)
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Taylor Seguin - Lab 1");

	// Create shapes for infaltable tube mans body

	sf::CircleShape circle(13);
	sf::RectangleShape bodyRect(sf::Vector2<float>(95.0f, 15.0f));
	sf::RectangleShape neckRect(sf::Vector2<float>(18.0f, 6.0f));
	sf::RectangleShape lowerLeftArmRect(sf::Vector2<float>(40.0f, 7.5f));
	sf::RectangleShape upperLeftArmRect(sf::Vector2<float>(32.0f, 7.5f));
	sf::RectangleShape lowerRightArmRect(sf::Vector2<float>(40.0f, 7.5f));
	sf::RectangleShape upperRightArmRect(sf::Vector2<float>(32.0f, 7.5f));

	// Set the colors of the created shapes

	circle.setFillColor(sf::Color::Red);
	bodyRect.setFillColor(sf::Color::Green);
	neckRect.setFillColor(sf::Color::Yellow);
	upperRightArmRect.setFillColor(sf::Color::Yellow);
	lowerRightArmRect.setFillColor(sf::Color::Red);
	upperLeftArmRect.setFillColor(sf::Color::Yellow);
	lowerLeftArmRect.setFillColor(sf::Color::Red);

	bool keyHeld = false;

	bool growing = true;

	// bodyRotation is the amount the body will be able to rotate. rotateCount and rotateDirection are for determining which direction the object will rotate. Left or right.
	int bodyRotation = 500;
	int rotateCount = 0;
	int rotateDirection = 0;

	// Set the origin and rotation of the body to orient the inflatable tube man

	bodyRect.setOrigin(15.0f, 5.0f);
	bodyRect.setPosition(300, 600);

	// Scale on x axis smaller then scale on y to add a cool squished movement effect
	bodyRect.setScale(3, 4);
	bodyRect.setRotation(-90);

	// Create positions for the body parts

	sf::Vector2<float> rightArmPosition((bodyRect.getLocalBounds().width), (bodyRect.getLocalBounds().height));
	sf::Vector2<float> leftArmPosition((bodyRect.getLocalBounds().width) - 6.0f, (bodyRect.getLocalBounds().height / 2.5f) - 4.0f);
	sf::Vector2<float> headPosition((neckRect.getLocalBounds().width), -6.0f);
	sf::Vector2<float> neckPosition((bodyRect.getLocalBounds().width), (bodyRect.getLocalBounds().height) / 2.5f);

	// Create body part origins

	sf::Vector2<float> headOrigin(1.0f, 1.0f);
	sf::Vector2<float> upperArmOrigin(0.0f, 1.0f);
	sf::Vector2<float> rightArmOrigin(0.0f, 1.0f);
	sf::Vector2<float> leftArmOrigin(0.0f, 0.0f);



	// set body part origins

	neckRect.setOrigin(upperArmOrigin);
	circle.setOrigin(headOrigin);
	upperRightArmRect.setOrigin(upperArmOrigin);
	upperLeftArmRect.setOrigin(upperArmOrigin);
	lowerRightArmRect.setOrigin(rightArmOrigin);
	lowerLeftArmRect.setOrigin(leftArmOrigin);

	// set the rotation angle of the body parts

	neckRect.setRotation(4.2f);
	upperLeftArmRect.setRotation(-69.0f);
	upperRightArmRect.setRotation(69.0f);
	lowerLeftArmRect.setRotation(-360.0f);
	lowerRightArmRect.setRotation(360.0f);

	// Set the position of the tube mans body parts

	circle.setPosition(headPosition);
	neckRect.setPosition(neckPosition);
	upperRightArmRect.setPosition(rightArmPosition);
	lowerRightArmRect.setPosition((upperRightArmRect.getLocalBounds().width), 1.5f);
	upperLeftArmRect.setPosition(leftArmPosition);
	lowerLeftArmRect.setPosition((upperLeftArmRect.getLocalBounds().width) -1.5f , 1.5f);

	// Add transformations

	TransformNode head(&circle);
	TransformNode neck(&neckRect);
	TransformNode body(&bodyRect);
	TransformNode upperLeftArm(&upperLeftArmRect);
	TransformNode lowerLeftArm(&lowerLeftArmRect);
	TransformNode upperRightArm(&upperRightArmRect);
	TransformNode lowerRightArm(&lowerRightArmRect);

	body.AddChild(&upperRightArm);
	body.AddChild(&upperLeftArm);
	body.AddChild(&neck);
	neck.AddChild(&head);
	upperRightArm.AddChild(&lowerRightArm);
	upperLeftArm.AddChild(&lowerLeftArm);

	sf::Clock deltaTime;
	while (window.isOpen())
	{
		float elaspedTime = deltaTime.restart().asSeconds();

		/*circle.scale(scaleFactor, scaleFactor);
		float currentScale = circle.getScale().x;
		if (currentScale >= 4.0f) {
		scaleFactor = shrinkFactor;
		}
		else if (currentScale <= 1.0f)
		{
		scaleFactor = growthFactor;
		}*/

		sf::Event sfEvent;
		while (window.pollEvent(sfEvent))
		{
			if (sfEvent.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (sfEvent.type == sf::Event::KeyReleased)
			{
				keyHeld = false;
			}
			else if (sfEvent.type == sf::Event::KeyPressed)
			{
				keyHeld = true;
			}
		}

		if (!keyHeld)
		{
			// Use an angle amount and multiply it by the elapsed time to find a new angle to move that body part to.
			float angleAmount = 69.0f;
			float anglePosition = angleAmount * elaspedTime;
			float bodyAngle = anglePosition;

			if (rotateCount < bodyRotation && rotateDirection == 0) {
				if (bodyAngle < 0) {
					bodyAngle *= -1;
				}

				++rotateCount;

				if (rotateCount == bodyRotation) {
					rotateDirection = -1;
				}

			}
			else if(rotateCount > -bodyRotation && rotateDirection == -1){
				if (bodyAngle > 0) {
					bodyAngle *= -1;
				}

				--rotateCount;

				if (rotateCount == -bodyRotation) {
					rotateDirection = 0;
				}
			}

			bodyRect.rotate(bodyAngle);
			upperLeftArmRect.rotate(bodyAngle * 1.5);
			lowerLeftArmRect.rotate(bodyAngle * 2.5);
			upperRightArmRect.rotate(bodyAngle * 1.5);
			lowerRightArmRect.rotate(bodyAngle * 2.5);
			neckRect.rotate(bodyAngle *-1 * 2);
		}

		window.clear(); // draw fullscreen graphic

					/*	sf::Transform hierarchy = sf::Transform::Identity;

						window.draw(circle);
						hierarchy = hierarchy * circle.getTransform();

						window.draw(lowerArmRect, hierarchy); // DRAWING with the circle's transform.
						hierarchy = hierarchy * lowerArmRect.getTransform();

						window.draw(upperArmRect, hierarchy); // DRAWING*/

		body.Draw(&window);

		window.display();
	}

	return 0;
}