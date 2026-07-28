#include <stdio.h>
#include <string.h>
//this will be where we will place our character strings!
char covid_genome_800[] =  "CGCCCTACATCGCGTCTGCGGCCCAAGTACTATGAGGCTACCTACATCCGGGAAATGAGGCAGGGTCTGNACTACTTACATACGAGCAATATGTAGAGAAATAGCGTGTGGCCGGTTAGAACTAGACTGATTAATCGGACCCAAGTGCGGGATCCTAGTTTGACACCCCTATAACACCTTACTCCCGCCCCCGGCCGGATGCTCTGGCATTCCNGTGCACAGGGGTTATGAACCAGGTGCCTTTNATTTCTTGGCAGTNGCGGACGTCCGGGCATTTTCTGGTATCTCATAGCGTGACATTCGCCATNTTATTCTTTTCCGTAGGGCCCTTNCCCCAGCACACACTACTGTGGGATCCGTGGTCTAACTAACAGATTGACTTAATGCATCGTACCANTCATACGGCACACCGGTCGTCTTGGTATCGCTAACTTGCTAATCCGCGCGTTGTTTCCTGGCAGGACTTGGGTTGTCGCTTCGTCCGTACTGAACAGTTCTCCATGCCTCTAAACCCGAGGCCATAACATACATGCTAGGCCTGTGAGGAACCTTGAAGCGACAANACACCTAGAGTGTCCCACTCTACCTGACGTATTGCGCCTGCCTTTTTGAGCAAAAGTAGTCCACAAATGTGCCGCGGATAATTTGTCTGTCCTATAGGATTCCCGCCCGCTGGCCTTATCTCCAGTGCAGAAATCTCTACGTCCCAGTCCATTCAATAAGCGGAATTAACCGATCCGTGAGNAGGCTGTCCTACGAGTGATTCCAGGAGGATCCCTTGTCTTGGTACAATACTGGTA";
char fastq_scores_800[] = ":,:=F11@8D+2=7@8=2B8:EF888/C>=>@A97-F8,IC3-4G>+5?7I-?G??;@;6B0@B@;BEH!=48.:;/+>19-5H7@CA5,58G5H4860E4982+4GGH431FH6E=H>?.+8./=0,E<G4>>4/=8:6+-.FG:+:/<-C/01EA2EE7@;:4,--H::0F73>>5AD2?H0A>39/250I-H8/7E;=6,E8-0I6B6H2!CC-B8?I/B@+/.A53A8852?547B8I<H!+8G6;6I4/>F>0!8I<5+?/57HHC=C.G3HB;FBH?/;3;-/;?A.4B9C/407D/>794!I<H;<12:IGH4C6@<@D=G?<0!B@E3.3=0+75+633.2@>5G/CD?IB4==@:AB:IIC59D1+?1DE>96+B2-,;F0F/-1C:!8+DC-2E,77-0I::604.,F,:0/I90E/6-1,>;IH/F/,1IF:6/..E@I=@@C7HA0<FG170E8;3;B1B0;F,B5,71-AF:2I/>82B?8,D6I1/7A77?3<B4D=85A<A,,9I5-9?<D;B+C=7<0?78G,@;=+@6=8.A4;9+D7B7AH@2,!1.GH8;772/II5+@+I>G<E23:65/+97C>G?,:G@/E?BG=:D72E4B729B+B<B@71+9D,+2/58;9:.EB>B812,/,<:,:.I0D6@G5D,C<6/>:79/+68/G@B?=B1H7F6GB82/4E5D/;F+024A4>CB2+,FC2EFHHCGEA@1IEB<5G,E4C=G?9;5G-;=@!/B0A@-660>A9;?5+3E3??7-G>FGG:-0G7808-II:F.>G=429H1146?,";
char dna;
char fastq;
int count = 0; 
int total_score = 0;
//need a function that somewhat imitates the null_terminator_checker
int score_compute(char character){
    return (int)character - 33;
}
int main(void){
    //conduct a preload
    dna = covid_genome_800[count];
    fastq = fastq_scores_800[count];    
    while(dna != '\0'){//constantly check if dna is a null terminator!
        dna = covid_genome_800[count];
        fastq = fastq_scores_800[count];
        if(dna != 'N'){//if N skip the computation!
            total_score+=score_compute(fastq);
        }
        count+=1;
    }
    printf("TOTAL: %d\n",total_score);
    printf("SCORE: %.1f%%\n",(float)total_score/400);
    // printf("This is my character: %c\n",covid_genome_800[0]);
    // printf("This is my integer of my character '%c' FASTQ: %d\n",fastq_scores_800[0],fastq_scores_800[0]);
    // printf("Here is a computed score : %d\n",score_compute(':'));
    return 0;

}