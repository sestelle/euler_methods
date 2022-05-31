#include "euler_methods.h"

static int	choose_step(double *step);
static void	exact_method(double step, FILE *file);
static void	explicit_method(double step, FILE *file);
static void	implicit_method(double step, FILE *file);
static void	trapezoidal_method(double step, FILE *file);

int		main(void)
{
	double	step;
	FILE	*file;

	if (choose_step(&step) != 0)
	{
		printf("Error: Invalid value of step\n");
		return (1);
	}

	if ((file = fopen("results.csv", "w")) == NULL)
	{
		printf("Error: Couldnt create file of results\n");
		return (1);
	}

	fprintf(file, "%s", "Time, Exact method, Explicit method, Implicit method, Trapezoidal method\n");

	for (int i = 0; i < COUNT; i++)
	{
		fprintf(file, "%lf,", i * step * pow(10, 9));

		exact_method(step, file);
		explicit_method(step, file);
		implicit_method(step, file);

		if (i != 0)
			trapezoidal_method(step, file);
		else
			fprintf(file, "%lf", U);

		fprintf(file, "\n");
	}

	printf("Info: Results with step %lf ns saved in results.csv file\n", step * pow(10, 9));

	fclose(file);

	return (0);
}

static int	choose_step(double *step)
{
	int		var = 0;

	printf("Choose step (1. H < 2RC; 2. H = 2RC; 3. H > 2RC): ");

	scanf("%d", &var);

	switch (var)
	{
		case 1:
			*step = 0.1 * R * C;
			break ;
		
		case 2:
			*step = 2 * R * C;
			break ;

		case 3:
			*step = 4 * R * C;
			break ;

		default:
			return (1);
	}

	printf("Info: Choosen step is %lf ns\n", *step * pow(10, 9));
	
	return (0);
}

static void	exact_method(double step, FILE *file)
{
	static double	t = 0;
	double			fi = 0;

	fi = U * exp(-(t / (R * C)));
	t = t + step;

	fprintf(file, "%.12lf,", fi);
}

static void	explicit_method(double step, FILE *file)
{
	static int	i = 0;
	double		fi = 0;

	fi = U * pow(1 - (step / (R * C)), i);
	i = i + 1;
	
	fprintf(file, "%.12lf,", fi);
}

static void	implicit_method(double step, FILE *file)
{
	static int	i = 0;
	double		fi = 0;

	fi = U / pow(1 + (step / (R * C)), i);
	i = i + 1;
	
	fprintf(file, "%.12lf,", fi);
}

static void	trapezoidal_method(double step, FILE *file)
{
	static double	fi = U;

	fi = ((fi * (1 - (step / (R * C)))) + (fi / (1 + (step / (R * C))))) / 2;
	
	fprintf(file, "%.12lf", fi);
}
