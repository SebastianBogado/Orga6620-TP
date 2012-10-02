PARSE_MANAGER lineas: 208 
ARCHIVO 0, LINEAS 208 
          
			    Esta informacion puede mostrar qu� piezas del programa son mas lentas de lo esperado, convirti�ndolas en candidatas para su reescritura en la etapa de optimizaci�n.






















































 
            Sebasti�n Javier Bogado, \textit{Padr�n Nro. 91.707}                     \\
            \normalsize{66.20 Organizaci�n de Computadoras}                             \\
            \normalsize{Facultad de Ingenier�a, Universidad de Buenos Aires}            \\
            \normalsize{Grupo Nro. 0 - 2do. Cuatrimestre de 2012}                       \\
            \texttt{ alemarra@gmail.com }                                              \\
            \texttt{ sebastian.j.bogado@gmail.com }                                              \\
       }
 \item \textbf{Profiling}: El profiling permite aprender donde el programa pasa la mayor parte de su tiempo, y cuales funciones llaman a otras mientras se ejecuta. 
 \item real: \%e, tiempo total real usado por el proceso.
 \item sys : \%S, total de segundos-CPU utilizados por el systema en nombre del proceso.
 \item user: \%U, total de segundos-CPU usados por el proceso directamente.
$^{*}$ Referencia: 
% (latin1 es ISO 8859-1).
% Citas bibliogr�ficas.
% Definici�n del tipo de documento.                                           %
% Inclusi�n de una imagen en formato EPS (Encapsulated Postscript).
% Informaci�n sobre los autores.
% Inserta el t�tulo.
% Los paquetes permiten ampliar las capacidades de LaTeX.                     %
% Paquete para definir el idioma usado.
% Paquete para definir la codificaci�n del conjunto de caracteres usado
% Paquete para inclusi�n de gr�ficos.
% Posibles clases de documentos: article, report, book, slides                %
% Posibles tama�os de letra: 10pt, 11pt, 12pt                                 %
% Posibles tipos de papel: a4paper, letterpaper, legalpapper                  %
% Quita el n�mero en la primer p�gina.
% Resumen
% T�tulo principal del documento.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%\includegraphics[width=0.5\textwidth]{fig001.eps}
%\usepackage{multicolumn} 
&   & Ordenado & Invertido & Aleatorio & Ordenado & Invertido & Aleatorio \\ \cline{1-8}
& & \multicolumn{3}{ c|}{Quicksort} & \multicolumn{3}{c|}{Stooge sort}\\ \cline{3-8}
A partir de ah�, el Stooge sort ya hace suficiente uso del procesador como para ser notado por time, mientras que el Quicksort hace lo propio reci�n en l muestra m�s grande, de 1024kb. En este caso, el Stooge sort se torn� intolerable.
Adem�s de los archivos indicados en el enunciado, fueron agregadas mediciones sobre archivos con tama�os arbitrarios, mayores, con el fin de mostrar de mejor manera las diferencias entre algoritmos.
Approach,'' 3ra Edici�n, Morgan Kaufmann Publishers, 2000.
El presente trabajo busca crear un programa que permita el ordenamiento de archivos a trav�s de dos implementaciones distintas, una utilizando el algoritmo Quicksort y la otra el algoritmo Stooge sort.\\
En la figura~\ref{fig001} se muestra el gr�fico del tiempo insumido por el Quicksort para las distintas muestras.\\
En la figura~\ref{fig002} se muestra el gr�fico del tiempo insumido por el Stooge sort para las distintas muestras, a excepci�n de la de 1024kb, porque demanda una escala que har�a inapreciable la situaci�n de las otras muestras.
En la figura~\ref{fig003} se muestra un ejemplo de c�mo presentar las ilustraciones del informe.
En la tabla~\ref{tab001} se presentan las mediciones realizadas con \textbf{time} sobre ambos algoritmos de ordenamiento y con archivos de distintos tama�os.\\
Gr�fico de speedup, quick vs stooge
Haremos uso entonces de dos herramientas distintas, el profiling del c�digo (por medio de \extit{gprof}) y la medici�n de los tiempos de ejecuci�n (por medio de \textit{time}). 
However, how your program is run will affect the information that shows up in the profile data. 
If you don't use some feature of your program while it is being profiled, no profile information will be generated for that feature.
It can also tell you which functions are being called more or less often than you expected. This may help you spot bugs that had otherwise been unnoticed.
La marcada diferencia entre la complejidad de los algoritmos se refleja en muestras tan chicas como la de 8kb. 
Muchas veces tanto para programas reci�n terminados, como para aquellos que llevan un tiempo en funcionamiento, se desconoce realmente qu� partes del programa insumen la mayor cantidad de recursos, sean estos de tiempo, carga de cpu, etc.
Para esto haremos uso de los programas \textbf{time} y \textbf{gprof}.
Para realizar el profiling tomamos una muestra suficientemente grande como para que las funciones mismas de\textbf{gprof} tuvieran una incidencia despreciable en la prueba. 
Poseer esta informaci�n se torna en algo cr�tico cuando se busca realizar una mejora de performance en dicho programa. Ser�a poco �til intentar optimizar a ciegas, por no decir in�til.\\
Profiling allows you to learn where your program spent its time and which functions called which other functions while it was executing.
Se present� un modelo para que los alumnos puedan tomar como referencia en la redacci�n de sus informes de trabajos pr�cticos.
Since the profiler uses information collected during the actual execution of your program, it an be used on programs that are too large or too complex to analyze by reading the source. 
Sobre este programa, luego, se realizar�n una serie de mediciones con el fin de determinar los desempe�os relativos de cada implementaci�n y las posibles mejoras a realizar. 
This information can show you which pieces of your program are slower than you expected, and might be candidates for rewriting to make your program execute faster. 
\author{	Alejandro Garc�a Marra, \textit{Padr�n Nro. 91.516}                     \\
\begin{abstract}
\begin{center}
\begin{center}
\begin{center}
\begin{center}
\begin{document}
\begin{figure}[!htp]
\begin{figure}[!htp]
\begin{figure}[!htp]
\begin{itemize}
\begin{itemize}
\begin{table}[!htp]
\begin{tabular}{cc|c|c|c|c|c|c|} 
\begin{thebibliography}{99}
\bibitem{HEN00} J. L. Hennessy and D. A. Patterson, ``Computer Architecture. A Quantitative
\bibitem{INT06} Intel Technology \& Research, ``Hyper-Threading Technology,'' 2006, http://www.intel.com/technology/hyperthread/.
\bibitem{LAR92} J. Larus and T. Ball, ``Rewriting Executable Files to Mesure Progam Behavior,'' Tech. Report 1083, Univ. of Wisconsin, 1992.
\caption{Facultad de Ingenier�a $-$ Universidad de Buenos Aires.} \label{fig003}
\caption{Resultados comando Time } \label{tab001}
\caption{Tiempo tomado para distintas muestras del Quicksort.} \label{fig001}
\caption{Tiempo tomado para distintas muestras del Stooge sort.} \label{fig002}
\cline{3-8}
\date{}
\documentclass[a4paper,10pt]{article}
\end{abstract}
\end{center}
\end{center}
\end{center}
\end{center}
\end{document}
\end{figure}
\end{figure}
\end{figure}
\end{itemize}
\end{itemize}
\end{table}
\end{tabular}
\end{thebibliography}
\includegraphics[width=1.1\textwidth]{stoogesort.png}
\includegraphics[width=1\textwidth]{quicksort.png}
\maketitle
\multicolumn{1}{|c|}{real$^{*}$} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{2-8}
\multicolumn{1}{|c|}{real} & 0.00 & 0.00 &0.00 & 0.00 & 0.02 & 0.02 \\ \cline{2-8}
\multicolumn{1}{|c|}{real} & 0.00 & 0.00 &0.00 & 0.02 & 0.02 & 0.01 \\ \cline{2-8}
\multicolumn{1}{|c|}{real} & 0.00 & 0.00 &0.00 & 0.17 & 0.17 & 0.17 \\ \cline{2-8}
\multicolumn{1}{|c|}{real} & 0.00 & 0.00 &0.00 & 1.44 & 1.44 & 1.44 \\ \cline{2-8}
\multicolumn{1}{|c|}{rea} & 0.04 & 0.03 &0.03 & $>$1500 & $>$1500 & $>$1500 \\ \cline{2-8}
\multicolumn{1}{|c|}{sys$^{*}$} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{sys} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{sys} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{sys} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{sys} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{sys} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{1-8}
\multicolumn{1}{|c|}{user$^{*}$} & 0.00 & 0.00 &0.00 & 0.00 & 0.00 & 0.00 \\ \cline{2-8}
\multicolumn{1}{|c|}{user} & 0.00 & 0.00 &0.00 & 0.01 & 0.01 & 0.01 \\ \cline{2-8}
\multicolumn{1}{|c|}{user} & 0.00 & 0.00 &0.00 & 0.17 & 0.17 & 0.17 \\ \cline{2-8}
\multicolumn{1}{|c|}{user} & 0.00 & 0.00 &0.00 & 1.44 & 1.43 & 1.44 \\ \cline{2-8}
\multicolumn{1}{|c|}{user} & 0.00 & 0.00 &0.00 &0.00 & 0.01 & 0.02 \\ \cline{2-8}
\multicolumn{1}{|c|}{user} & 0.03 & 0.02 &0.03 & $>$1500 & $>$1500 & $>$1500 \\ \cline{2-8}
\multicolumn{1}{|c}{\multirow{3}{*}{1024kb}} &
\multicolumn{1}{|c}{\multirow{3}{*}{16kb}} &
\multicolumn{1}{|c}{\multirow{3}{*}{32kb}} &
\multicolumn{1}{|c}{\multirow{3}{*}{64kb}} &
\multicolumn{1}{|c}{\multirow{3}{*}{8kb}} &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\multicolumn{1}{|c}{}                        &
\muticolumn{1}{|c}{\multirow{3}{*}{1kb}} &
\newpage
\newpage
\section{Conclusiones}
\section{Introducci�n}
\section{Mediciones}
\section{Profiling}
\subsection{An�lisis de los datos}
\subsection{Valores Obtenidos}
\thispagestyle{empty}
\title{		\textbf{Trabajo pr�ctico 0: Infraestructura b�sica}}
\usepackage[latin1]{inputenc}
\usepackage[panish]{babel}
\usepackage{graphicx}
\usepackage{multirow} 
