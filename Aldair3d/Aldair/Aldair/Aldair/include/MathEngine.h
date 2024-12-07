#pragma once
namespace MathEngine {
	//Codigo Proporcionado: "Roberto Charreton".
	// Constantes matem�ticas
	constexpr float PI = 3.14159265358979323846f;
	constexpr float E = 2.71828182845904523536f;

	/**
	 * @brief Calcula la ra�z cuadrada mediante el m�todo Newton-Raphson.
	 * El valor para calcular la ra�z cuadrada de la ra�z cuadrada calculada.
	*/
	inline float sqrt(float value) {
		if (value < 0) {
			return 0;
		}
		float x = value;
		float y = 1.0f;
		float epsilon = 0.00001f; // Precisi�n deseada en el calculo.
		while (x - y > epsilon) {
			x = (x + y) / 2.0f;
			y = value / x;
		}
		return x;
	}

	// Calcula el seno de un �ngulo en radianes.
	inline float sin(float angle) {
		float result = 0.0f;
		float term = angle;
		float angle_squared = angle * angle;
		int n = 1;
		while (term > 1e-6f || term < -1e-6f) {
			result += term;
			term *= -angle_squared / ((2 * n) * (2 * n + 1));
			++n;
		}
		return result;
	}

	//Calcula el coseno de un �ngulo en radianes
	inline float cos(float angle) {
		return sin(angle + PI / 2);
	}

	//Calcula la tangente de un �ngulo en radianes.
	inline float tan(float angle) {
		float s = sin(angle);
		float c = cos(angle);
		return c != 0.0f ? s / c : 0.0f; // Evita la divisi�n por cero
	}
};