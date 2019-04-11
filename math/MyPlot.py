

import matplotlib.pyplot as plt


class MyPlot:
    def __init__(self) :
        return

    def initplot(self, row=3, col=4, figsize=(15,8), hspace=0.5, wspace=0.4) :
        self.plotidx=0
        self.plotr=row
        self.plotc=col
        plt.figure(figsize=figsize)
        plt.subplots_adjust(hspace=hspace, wspace=wspace)

    def nextplot(self):
        self.plotidx=self.plotidx+1
        plt.subplot(self.plotr, self.plotc, self.plotidx)


    def show(self):
        plt.show()

