//A program to solve electrical circuits using network theorem
#include<stdio.h>

int main()
{
    int ns,nr;
    printf("Enter the number of sources: ");
    scanf("%d",&ns);
    printf("Enter the number of resistors: ");
    scanf("%d",&nr);

    int i,j,k,sfrom[ns],sto[ns],from[nr],to[nr];
    float value[ns],resistance[nr];
    char source[ns][3],branch[nr][3];
    
    for(i=0;i<ns;i++)
    {
        scanf("%s",source[i]);
        scanf("%d %d %f",&sfrom[i],&sto[i],&value[i]);
    }

    for(i=0;i<nr;i++)
    {
        scanf("%s",branch[i]);
        scanf("%d %d %f",&from[i],&to[i],&resistance[i]);
    }

    int max_from_nodes=0,max_to_nodes=0;
    for(i=0;i<nr;i++)
    {
        if(from[i]>max_from_nodes)
        max_from_nodes = from[i];
        if(to[i]>max_to_nodes)
        max_to_nodes = to[i];
    }

    int max_nodes;
    if(max_from_nodes < max_to_nodes)
    max_nodes = max_to_nodes;
    else
    max_nodes = max_from_nodes;

    int matrix[max_nodes][nr];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<nr;j++)
        matrix[i][j] = 0;
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<nr;j++)
        {
            if(to[j]==i+1)
            matrix[i][j] = -1;
            if(from[j]==i+1)
            matrix[i][j] = 1;
        }
    }

    printf("\nIncidence Matrix: \n");
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<nr;j++)
        printf("%d ",matrix[i][j]);
        printf("\n");
    }

    float admittance_matrix[nr][nr];
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nr;j++)
        admittance_matrix[i][j] = 0.0;
    }

    for(i=0;i<nr;i++)
    {
        for(j=0;j<nr;j++)
        {
            if(i==j)
            admittance_matrix[i][j] = 1/resistance[i];
        }
    }

    printf("\nAdmittance Matrix: \n");
    for(i=0;i<nr;i++)
    {
        for(j=0;j<nr;j++)
        printf("%0.2f ",admittance_matrix[i][j]);
        printf("\n");
    }

    int transpose_matrix[nr][max_nodes];
    for(i=0;i<nr;i++)
    {
        for(j=0;j<max_nodes;j++)
        transpose_matrix[i][j] = matrix[j][i];
    }

    float result1[max_nodes][nr];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<nr;j++)
        {
            result1[i][j] = 0.0;
        }
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<nr;j++)
        {
            for(k=0;k<nr;k++)
            result1[i][j] += (float) matrix[i][k] * admittance_matrix[k][j];
        }
    }

    float result2[max_nodes][max_nodes];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<max_nodes;j++)
        result2[i][j] = 0.0;
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<max_nodes ;j++)
        {
            for(k=0;k<nr;k++)
            result2[i][j] += result1[i][k] * (float) transpose_matrix[k][j];
        }
    }

    float source_voltage_matrix[nr][1],source_current_matrix[nr][1];
    for(i=0;i<nr;i++)
    {
        source_voltage_matrix[i][0] = 0.0;
        source_current_matrix[i][0] = 0.0;
    }

    for (i=0;i<ns;i++) 
    {
        if(source[i][0]=='V' || source[i][0]=='v')
        {
            for(j=0;j<nr;j++)
            {
                if(from[j]==sfrom[i] && to[j]==sto[i])
                source_voltage_matrix[j][0] = value[i];
            }
        }

        if(source[i][0]=='I' || source[i][0]=='i')
        {
            for(j=0;j<nr;j++)
            {
                if(from[j]==sfrom[i] && to[j]==sto[i])
                source_current_matrix[j][0] = value[i];
            }
        }
    }

    printf("\nSource Voltage Matrix: \n");
    for(i=0;i<nr;i++)
    {
        for(j=0;j<1;j++)
        printf("%0.2f ",source_voltage_matrix[i][j]);
        printf("\n");
    }

    printf("\nSource Current Matrix: \n");
    for(i=0;i<nr;i++)
    {
        for(j=0;j<1;j++)
        printf("%0.2f ",source_current_matrix[i][j]);
        printf("\n");
    }

    float result3[max_nodes][1];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        result3[i][j] = 0.0;
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        {
            for(k=0;k<nr;k++)
            result3[i][j] += result1[i][k] * source_voltage_matrix[k][j];
        }
    }

    float result4[max_nodes][1];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        {
            result4[i][j] = 0.0;
        }
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        {
            for(k=0;k<nr;k++)
            {
                result4[i][j] += (float) matrix[i][k] * source_current_matrix[k][j];
            }
        }
    }

    float result5[max_nodes][1];
    for(i=0;i<max_nodes;i++)
    result5[i][0] = result3[i][0] - result4[i][0];

    float result2_inverse[max_nodes][max_nodes];

    for (int i = 0; i < max_nodes; i++) 
    {
        for (int j = 0; j < max_nodes; j++) 
        result2_inverse[i][j] = (i == j)? 1.0:0.0;  
    }
    for (int i = 0; i < max_nodes; i++) 
    {
        int maxRow = i;
        for (int j = i + 1; j < max_nodes; j++) 
        {
            if (result2[j][i] > result2[maxRow][i]) 
            {
                maxRow = j;
            }
        }
        if (maxRow != i) 
        {
            for (int k = 0; k < max_nodes; k++) 
            {
                float temp = result2[i][k];
                result2[i][k] = result2[maxRow][k];
                result2[maxRow][k] = temp;
                
                temp = result2_inverse[i][k];
                result2_inverse[i][k] = result2_inverse[maxRow][k];
                result2_inverse[maxRow][k] = temp;
            }
        }
        float pivot = result2[i][i];
        for (int j = 0; j < max_nodes; j++) 
        {
            result2[i][j] /= pivot;
            result2_inverse[i][j] /= pivot;
        }
        for (int j = 0; j < max_nodes; j++) 
        {
            if (j != i) 
            {
                float factor = result2[j][i];
                for (int k = 0; k < max_nodes; k++) 
                {
                    result2[j][k] -= factor * result2[i][k];
                    result2_inverse[j][k] -= factor * result2_inverse[i][k];
                }
            }
        }
    }

    float result6[max_nodes][1];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        result6[i][j] = 0.0;
    }

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        {
            for(k=0;k<max_nodes;k++)
            result6[i][j] += result2_inverse[i][k] * result5[k][j];
        }
    }

    float Node_Volages[max_nodes][1];
    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        Node_Volages[i][j] = result6[i][j];
    }

    printf("\nFinal Voltages: \n");

    for(i=0;i<max_nodes;i++)
    {
        for(j=0;j<1;j++)
        printf("Voltage at node %d: %f ",i+1,Node_Volages[i][j]);
        printf("\n");
    }

    return 0;
}