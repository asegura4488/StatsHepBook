 double No = 0.;
 double Nb = 5.;
 double Ns = 1.;


double GetCLs(double mu){

  double CLb  =  TMath::Prob(2.*(Nb),2*(1.+No));
  double CLsb =  TMath::Prob(2.*(mu*Ns+Nb),2*(1.+No));

  return CLsb/CLb;

}

double GetUpperLimit(int N, double *Mu, double *pvalue){

  double upper = -1.;
  double delta = 0.0002;
  
  for(int i = 0; i < N; i++){
        if ( abs(pvalue[i]-0.05) < delta ){
  	//std::cout << Mu[i] << " " << pvalue[i] << std::endl;
  	upper = Mu[i];
  	}
  }
  
  
  return upper;  
}

void ModifiedUpperFrequentist(){

  
  int N = 20000;
  double *Mu = new double[N];
  double *pvalue = new double[N];
  double *Epvalue = new double[N];

  double mu = 0.;
  
  for(int i = 0; i < N; i++){
  	Mu[i] = mu;
  	pvalue[i] = GetCLs(mu);
  	Epvalue[i] = 0.05;
  	mu += 0.001;
  }


  double upperlimit = GetUpperLimit(N,Mu,pvalue);
  std::cout << upperlimit << std::endl;

  TCanvas *c = new TCanvas("c","Canvas",200,200,800,800);

  TGraph *gr1 = new TGraph(N,Mu,pvalue);
  TGraph *gr2 = new TGraph(N,Mu,Epvalue);
  
  gr1->SetTitle("Modified frequentist pvalue scan");
  
  gr1->SetLineColor(4);
  gr1->SetLineWidth(3);
 
  gr1->GetXaxis()->SetTitle("#mu");
  gr1->GetXaxis()->SetTitleSize(0.06);
  gr1->GetXaxis()->SetTitleOffset(0.6);
  
  gr1->GetYaxis()->SetTitle("p-value");
  gr1->GetYaxis()->SetTitleSize(0.06);
  gr1->GetYaxis()->SetTitleOffset(0.6);
  
  gr2->SetLineColor(2);
  gr2->SetLineWidth(3);

  gr1->Draw("AL");
  gr2->Draw("same");

  c->SaveAs("ModifiedCL.pdf");
}

int main (){

 ModifiedUpperFrequentist();
 return 0;
}
